#include "Scene.hpp"

using namespace DEM::Core;

DEM_UINT Scene::sm_id = 0;

Scene::Scene(std::string name)
{
	m_id = sm_id;
	sm_id++;
	m_name = name;
}

Scene::Scene(const Scene& scene)
{
	m_id = sm_id;
	sm_id++;
	m_name = scene.m_name;
	m_children = scene.m_children;
}

Scene::~Scene()
{
	for (Actor *actor : m_children)
	{
		delete actor;
		actor = 0;
	}
}

DEM_UINT Scene::size() const
{
	return m_children.size();
}

Scene& Scene::add(Actor *actor)
{
	m_children.emplace_back(actor);
	return *this;
}

Actor* Scene::get(std::string name)
{
	for (DEM_UINT i = 0; i < m_children.size(); ++i)
	{
		if (m_children.at(i)->getName() == name)
		{
			return m_children.at(i);
		}
	}
	return 0;
}

Actor* Scene::get(DEM_UINT id)
{
	for (DEM_UINT i = 0; i < m_children.size(); ++i)
	{
		if (m_children.at(i)->getId() == id)
		{
			return m_children.at(i);
		}
	}
	return 0;
}

std::vector<Actor*>::iterator* Scene::findById(DEM_UINT id)
{
	std::vector<Actor*>::iterator it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			return &it;
		}
	}
	return 0;
}

std::vector<Actor*>::iterator* Scene::findById(std::string name)
{
	std::vector<Actor*>::iterator it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			return &it;
		}
	}
	return 0;
}

Scene& Scene::remove(Actor *actor)
{
	if (!actor) { return *this; }

	std::vector<Actor*>::iterator it = m_children.begin(), rslt;
	bool found = false;
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getId() == actor->getId())
		{
			rslt = it;
			found = true;
			break;
		}
	}
	if (found)
	{
		m_children.erase(rslt, rslt + 1);
	}
	return *this;
}

DEM_UINT Scene::getId() const
{
	return m_id;
}

std::string Scene::getName() const
{
	return m_name;
}

void Scene::setName(const std::string& name)
{
	m_name = name;
}

std::vector<Actor*> Scene::getChildren() const
{
	return m_children;
}