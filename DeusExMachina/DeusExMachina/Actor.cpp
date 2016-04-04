#include "Actor.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;

DEM_UINT Actor::sm_id = 0;

Actor::Actor(string name)
{
	m_parent = 0;
	m_id = sm_id;
	sm_id++;
	m_name = name;
	
	srand((DEM_UINT)time(0));
	char key[16];
	for (DEM_UINT i = 0; i < 16; ++i)
	{
		DEM_UINT n = 65 + (rand() % 25);
		key[i] = (char)n;
	}
	m_uid = Crypto::Hash32(key);
}

Actor::Actor(const Actor& a)
{
	m_parent = 0;
	m_id = sm_id;
	sm_id++;
	m_name = a.m_name;

	srand((DEM_UINT)time(0));
	char key[16];
	for (DEM_UINT i = 0; i < 16; ++i)
	{
		DEM_UINT n = 65 + (rand() % 25);
		key[i] = (char)n;
	}
	m_uid = Crypto::Hash32(key);

	m_components = a.m_components;
}

Actor::~Actor()
{
	for (Component *comp : m_components)
	{
		delete comp;
		comp = 0;
	}
}

std::vector<Component*> Actor::getComponents() const
{
	return m_components;
}

string Actor::getName() const
{
	return m_name;
}
void Actor::setName(const string& name)
{
	m_name = name;
}

DEM_UINT Actor::getUid() const
{
	return m_uid;
}

DEM_UINT Actor::getId() const
{
	return m_id;
}

Actor& Actor::addComponent(Component *comp)
{
	comp->setParent(this);
	m_components.emplace_back(comp);
	return *this;
}

Actor* Actor::getParent() const
{
	return m_parent;
}

void Actor::setParent(Actor *actor)
{
	m_parent = actor;
	m_parent->addChild(this);
}

std::vector<Actor*> Actor::getChildren() const
{
	return m_children;
}

void Actor::setChildren(std::vector<Actor*> children)
{
	m_children = children;
}

void Actor::addChild(Actor *actor)
{
	m_children.emplace_back(actor);
	actor->m_parent = this;
}

void Actor::removeChildById(DEM_UINT id)
{
	bool found = false;
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		m_children.erase(it, it + 1);
	}
}
void Actor::removeChildByUid(DEM_UINT uid)
{
	bool found = false;
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getUid() == uid)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		m_children.erase(it, it + 1);
	}
}
void Actor::removeChildByName(std::string name)
{
	bool found = false;
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		m_children.erase(it, it + 1);
	}
}

Actor* Actor::findChildById(DEM_UINT id)
{
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			return (*it);
		}
	}
	return 0;
}
Actor* Actor::findChildByUid(DEM_UINT uid)
{
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getUid() == uid)
		{
			return (*it);
		}
	}
	return 0;
}
Actor* Actor::findChildByName(std::string name)
{
	std::vector<Actor*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			return (*it);
		}
	}
	return 0;
}