#include "Renderer.hpp"

using namespace DEM::Core;

#include "Mesh.hpp"

Renderer::Renderer(Camera *camera, Scene *scene)
{
	m_camera = camera;
	m_scene = scene;
	m_currentSceneIndex = 0;
	m_scenes.push_back(m_scene);
	m_enableSkybox = true;
	m_skyboxGeometry = 0;
	m_skyboxMaterial = 0;
}

Renderer::~Renderer()
{
	delete m_camera;
	
	for (Scene *scene : m_scenes)
	{
		delete scene;
		scene = 0;
	}
	delete m_scene;
	m_scene = 0;

	delete m_skyboxGeometry;
	m_skyboxGeometry = 0;

	delete m_skyboxMaterial;
	m_skyboxMaterial = 0;
}


Renderer& Renderer::addScene(Scene *scene)
{
	m_scenes.emplace_back(scene);
	return *this;
}

Renderer& Renderer::loadScene(DEM_UINT index)
{
	if (index >= 0 && index < m_scenes.size())
	{
		m_scene = m_scenes.at(index);
		for (DEM_UINT i = 0; i < m_scene->size(); ++i)
		{
			StartComponents(m_scene->get(i));
		}
	}
	return *this;
}

Renderer& Renderer::executeCmd(RenderCommand *cmd)
{
#if defined(DEM_DEBUG) && (DEM_DEBUG == 1)
	std::cout << cmd << std::endl;
#endif
	(*cmd)(this);
	return *this;
}

Renderer& Renderer::RenderActor(DEM_UINT index)
{
	Actor *actor = m_scene->get(index);
	if (actor)
	{
		actor->Render();

		std::vector<Actor*> children = actor->getChildren();
		for (DEM_UINT i = 0; i < children.size(); ++i)
		{
			children.at(i)->Render();
		}
	}
	return *this;
}

Renderer& Renderer::UpdateActor(DEM_UINT index)
{
	Actor *actor = m_scene->get(index);
	if (actor)
	{
		actor->Update();

		std::vector<Actor*> children = actor->getChildren();
		for (DEM_UINT i = 0; i < children.size(); ++i)
		{
			children.at(i)->Update();
		}
	}
	return *this;
}

Renderer& Renderer::StartComponents(Actor *actor)
{
	if (actor)
	{
		std::vector<Component*> comps = actor->getComponents();
		for (DEM_UINT i = 0; i < comps.size(); ++i)
		{
			comps.at(i)->Start();
		}

		std::vector<Actor*> children = actor->getChildren();
		for (DEM_UINT i = 0; i < children.size(); ++i)
		{
			std::vector<Component*> comps = children.at(i)->getComponents();
			for (DEM_UINT i = 0; i < comps.size(); ++i)
			{
				comps.at(i)->Start();
			}
		}
	}
	return *this;
}

Renderer& Renderer::UpdateComponent(Actor *actor, DEM_UINT index)
{
	if (actor)
	{
		std::vector<Component*> comps = actor->getComponents();
		for (DEM_UINT i = 0; i < comps.size(); ++i)
		{
			comps.at(i)->Update();
		}

		std::vector<Actor*> children = actor->getChildren();
		for (DEM_UINT i = 0; i < children.size(); ++i)
		{
			std::vector<Component*> comps = children.at(i)->getComponents();
			for (DEM_UINT i = 0; i < comps.size(); ++i)
			{
				comps.at(i)->Update();
			}
		}
	}
	return *this;
}

Camera* Renderer::getCamera()
{
	return m_camera;
}

void Renderer::setCamera(Camera* camera)
{
	m_camera = camera;
}

Scene* Renderer::getScene()
{
	return m_scene;
}

void Renderer::setScene(Scene* scene)
{
	m_scene = scene;
}

bool Renderer::isSkyboxEnabled() const
{
	return m_enableSkybox;
}

void Renderer::enableSkybox()
{
	m_enableSkybox = true;
}

void Renderer::disableSkybox()
{
	m_enableSkybox = false;
}

void Renderer::initSkybox()
{
	std::vector<Vertex*> skybox_vertice = {
		new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f)),
		new Vertex(Math::Vector3(1.0f, -1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, -1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, -1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)),
		new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f)),
		new Vertex(Math::Vector3(1.0f, -1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f)),
		new Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, 1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(1.0f, 1.0f, -1.0f)),
		new Vertex(Math::Vector3(1.0f, -1.0f, -1.0f)), new Vertex(Math::Vector3(1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, 1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(1.0f, 1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f)),
		new Vertex(Math::Vector3(1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f)), new Vertex(Math::Vector3(1.0f, -1.0f, 1.0f))
	};
	std::vector<GLuint> skybox_indices;
	for (unsigned int i = 0; i < skybox_vertice.size(); ++i){ skybox_indices.emplace_back(i); }

	m_skyboxGeometry = new Geometry(skybox_vertice, skybox_indices); 
	m_skyboxMaterial = new Material(DEFAULT_SKYBOX_VS, DEFAULT_SKYBOX_FS);
}

void Renderer::loadSkybox(const std::string& right, const std::string& left, const std::string& up, const std::string& down, const std::string& forward, const std::string& back)
{
	std::vector<std::string> paths;
	paths.emplace_back(right);
	paths.emplace_back(left);
	paths.emplace_back(up);
	paths.emplace_back(down);
	paths.emplace_back(forward);
	paths.emplace_back(back);

	if (m_skyboxGeometry != 0 && m_skyboxMaterial != 0)
	{
		(*m_skyboxMaterial)[DEM_SKYBOX_TEXTURE_UNIT]->setType(DEM_TEXTURE_TYPE::DEM_CUBEMAP);
		(*m_skyboxMaterial)[DEM_SKYBOX_TEXTURE_UNIT]->load(paths);
	}
}

void Renderer::renderSkybox()
{
	if (m_enableSkybox)
	{
		GLuint programID = m_skyboxMaterial->getShaderProgram()->getProgram();
		glDepthMask(GL_FALSE);
		m_skyboxMaterial->bind();

		PerspectiveCamera *camera = static_cast<PerspectiveCamera*>(m_camera);

		glm::mat4 view = glm::lookAtRH(glm::vec3(camera->eye.x, camera->eye.y, camera->eye.z),
			glm::vec3(camera->target.x, camera->target.y, camera->target.z),
			glm::vec3(camera->up.x, camera->up.y, camera->up.z));
		glm::mat4 proj = glm::perspective(camera->getFOV(), camera->getAspect(), camera->getNear(), camera->getFar());

		GLuint viewLocation = glGetUniformLocation(programID, "u_view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		GLuint projLocation = glGetUniformLocation(programID, "u_proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

		m_skyboxGeometry->bind();
		glDrawElements(GL_TRIANGLES, m_skyboxGeometry->getIndices().size(), GL_UNSIGNED_INT, (const void*)0);
		m_skyboxGeometry->unbind();

		m_skyboxMaterial->unbind();
		glDepthMask(GL_TRUE);
	}
}

Material* Renderer::getSkyboxMaterial() const
{
	return m_skyboxMaterial;
}