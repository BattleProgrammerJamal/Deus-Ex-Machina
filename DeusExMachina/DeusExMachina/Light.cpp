#include "Light.hpp"

using namespace DEM::Core;

std::vector<Light*> Light::sm_lights = std::vector<Light*>();

Light::Light()
	: Actor("Light")
{
	sm_lights.emplace_back(this);
	intensity = 1.0f;
	color.set(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::~Light()
{
	bool found = false;
	std::vector<Light*>::iterator it;
	for (it = sm_lights.begin(); it != sm_lights.end(); ++it)
	{
		if ((*it)->getId() == m_id)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		sm_lights.erase(it, it + 1);
	}
}

std::vector<Light*> Light::getLights()
{
	return sm_lights;
}

void Light::_dynamicReserve()
{
	if (sm_lights.size() == (sm_lights.capacity() - 1))
	{
		sm_lights.reserve(100);
	}
}