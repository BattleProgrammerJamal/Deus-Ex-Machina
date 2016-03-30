#include "Component.hpp"

using namespace DEM::Core;

DEM_UINT Component::sm_id = 0;

Component::Component()
{
	m_id = sm_id;
	sm_id++;
	m_parent = 0;
}

Component::~Component()
{
}

Actor* Component::getParent() const
{
	return m_parent;
}

void Component::setParent(Actor* actor)
{
	m_parent = actor;
}