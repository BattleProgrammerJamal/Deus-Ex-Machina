#include "Mesh.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;
using namespace DEM::Math;

DEM_UINT Mesh::sm_id = 0;
Clock* Mesh::clock = new Clock();

Mesh::Mesh(Geometry *geometry, Material *material, string name)
	: Actor(name)
{
	m_id = sm_id;
	++sm_id;
	m_geometry = geometry;
	m_material = material;
	drawStyle = GL_TRIANGLES;
	clock->start();
}

Mesh::Mesh(const Mesh& mesh)
{
	m_id = sm_id;
	++sm_id;
	m_geometry = new Geometry(*mesh.getGeometry());
	m_material = new Material(*mesh.getMaterial());
	drawStyle = mesh.drawStyle;
	clock->start();
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
	Camera *camera = renderer->getCamera();
	Scene *scene = renderer->getScene();

	m_material->bind();
	GLuint programID = m_material->getShaderProgram()->getProgram();

	GLuint worldLocation = glGetUniformLocation(programID, "u_world");
	glUniformMatrix4fv(worldLocation, 1, GL_FALSE, transform->World().ptr_value());

	GLuint viewLocation = glGetUniformLocation(programID, "u_view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, camera->getView().ptr_value());

	GLuint projLocation = glGetUniformLocation(programID, "u_proj");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, camera->getProj().ptr_value());

	GLuint timeLocation = glGetUniformLocation(programID, "time");
	glUniform1f(timeLocation, t);

	Vector3 eye = static_cast<PerspectiveCamera*>(camera)->eye;
	GLuint eyeLocation = glGetUniformLocation(programID, "u_eye");
	glUniform3f(eyeLocation, eye.x, eye.y, eye.z);

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