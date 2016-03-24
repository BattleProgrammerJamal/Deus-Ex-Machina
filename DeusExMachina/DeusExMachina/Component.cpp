#include "Component.hpp"

using namespace DEM::Core;

DEM_UINT Component::sm_id = 0;

Component::Component()
{
	m_id = sm_id;
	sm_id++;
}

Component::~Component()
{
}