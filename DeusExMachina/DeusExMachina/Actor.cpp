#include "Actor.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;

DEM_UINT Actor::sm_id = 0;

Actor::Actor(string name)
{
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