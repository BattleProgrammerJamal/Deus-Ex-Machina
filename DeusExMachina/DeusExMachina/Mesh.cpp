#include "Mesh.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;
using namespace DEM::Math;

DEM_UINT Mesh::sm_id = 0;
Clock* Mesh::clock = new Clock(true);

Mesh::Mesh(Geometry *geometry, Material *material, string name)
	: Actor(name)
{
	m_id = sm_id;
	++sm_id;
	m_geometry = geometry;
	m_material = material;
	drawStyle = GL_TRIANGLES;
}

Mesh::Mesh(const Mesh& mesh)
{
	m_id = sm_id;
	++sm_id;
	m_geometry = new Geometry(*mesh.getGeometry());
	m_material = new Material(*mesh.getMaterial());
	drawStyle = mesh.drawStyle;
}

Mesh::~Mesh()
{
	delete m_geometry;
	delete m_material;
}

void Mesh::Render()
{
	float t = clock->seconds();

	Renderer *renderer = DeusExMachina::Instance()->getRenderer();
	PerspectiveCamera *camera = static_cast<PerspectiveCamera*>(renderer->getCamera());
	Scene *scene = renderer->getScene();

	m_material->bind();
	GLuint programID = m_material->getShaderProgram()->getProgram();

	glm::mat4 T = glm::translate(glm::vec3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
	glm::mat4 R =	glm::rotate(transform->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f)) * 
					glm::rotate(transform->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
					glm::rotate(transform->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 S = glm::scale(glm::vec3(transform->getScale().x, transform->getScale().y, transform->getScale().z));
	glm::mat4 world = S * R * T;
	glm::mat4 view = glm::lookAtRH(glm::vec3(camera->eye.x, camera->eye.y, camera->eye.z), 
								glm::vec3(camera->target.x, camera->target.y, camera->target.z),
								glm::vec3(camera->up.x, camera->up.y, camera->up.z));
	glm::mat4 proj = glm::perspective(camera->getFOV(), camera->getAspect(), camera->getNear(), camera->getFar());

	GLuint worldLocation = glGetUniformLocation(programID, "u_world");
	glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(world));

	GLuint viewLocation = glGetUniformLocation(programID, "u_view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	GLuint projLocation = glGetUniformLocation(programID, "u_proj");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

	GLuint timeLocation = glGetUniformLocation(programID, "time");
	glUniform1f(timeLocation, t);

	Vector3 eye = static_cast<PerspectiveCamera*>(camera)->eye;
	GLuint eyeLocation = glGetUniformLocation(programID, "u_eye");
	glUniform3f(eyeLocation, eye.x, eye.y, eye.z);

	DEM_UINT index = 0;
	for (Light *L : Light::getLights())
	{
		std::stringstream lightColorStream, lightIntensityStream;
		lightColorStream << "u_lights[" << index << "].color";
		lightIntensityStream << "u_lights[" << index << "].intensity";

		GLuint lightColorLocation = glGetUniformLocation(programID, lightColorStream.str().c_str());
		GLuint lightIntensityLocation = glGetUniformLocation(programID, lightIntensityStream.str().c_str());

		glUniform4f(lightColorLocation, L->color.r, L->color.g, L->color.b, L->color.a);
		glUniform1f(lightIntensityLocation, L->intensity);

		if (typeid(*L) == typeid(DirectionalLight))
		{
			DirectionalLight *dLight = static_cast<DirectionalLight*>(L);

			std::stringstream lightPositionStream, lightDirectionStream, lightTypeStream;
			lightPositionStream << "u_lights[" << index << "].position";
			lightDirectionStream << "u_lights[" << index << "].direction";
			lightTypeStream << "u_lights[" << index << "].type";

			GLuint lightPositionLocation = glGetUniformLocation(programID, lightPositionStream.str().c_str());
			GLuint lightDirectionLocation = glGetUniformLocation(programID, lightDirectionStream.str().c_str());
			GLuint lightTypeLocation = glGetUniformLocation(programID, lightTypeStream.str().c_str());

			glUniform3f(lightPositionLocation, dLight->position.x, dLight->position.y, dLight->position.z);
			glUniform3f(lightDirectionLocation, dLight->direction.x, dLight->direction.y, dLight->direction.z);
			glUniform1i(lightTypeLocation, 1);
		}
		else
		{
			if (typeid(*L) == typeid(PointLight))
			{
				PointLight *pLight = static_cast<PointLight*>(L);

				std::stringstream lightPositionStream, lightTypeStream;
				lightPositionStream << "u_lights[" << index << "].position";
				lightTypeStream << "u_lights[" << index << "].type";

				GLuint lightPositionLocation = glGetUniformLocation(programID, lightPositionStream.str().c_str());
				GLuint lightTypeLocation = glGetUniformLocation(programID, lightTypeStream.str().c_str());

				glUniform3f(lightPositionLocation, pLight->position.x, pLight->position.y, pLight->position.z);
				glUniform1i(lightTypeLocation, 0);
			}
		}

		++index;
	}

	if (typeid(*m_geometry) == typeid(MorphTargetGeometry))
	{
		DEM_UINT morph_target_index = 0;
		MorphTargetGeometry *mtGeometry = static_cast<MorphTargetGeometry*>(m_geometry);
		for (MorphTarget *mt : mtGeometry->getMorphTargets())
		{
			std::strstream stream;
			stream << "u_morphTargetWeight" << morph_target_index << '\0';

			GLuint morphTargetWeightLocation = glGetUniformLocation(programID, stream.str());
			glUniform1f(morphTargetWeightLocation, mt->weight);

			++morph_target_index;
		}
	}

	m_geometry->bind();
	glDrawElements(drawStyle, m_geometry->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);
	m_geometry->unbind();

	m_material->unbind();
}

void Mesh::Update()
{
}

Geometry* Mesh::getGeometry() const
{
	return m_geometry;
}

void Mesh::setGeometry(Geometry* geometry)
{
	m_geometry = geometry;
}

Material* Mesh::getMaterial() const
{
	return m_material;
}

void Mesh::setMaterial(Material* material)
{
	m_material = material;
}

Clock* Mesh::getClock()
{
	return clock;
}