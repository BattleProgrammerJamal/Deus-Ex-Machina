#include "Renderer.hpp"

using namespace DEM::Core;

Renderer::Renderer(Camera *camera, Scene *scene)
{
	m_camera = camera;
	m_scene = scene;
	m_currentSceneIndex = 0;
	m_scenes.push_back(m_scene);
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
