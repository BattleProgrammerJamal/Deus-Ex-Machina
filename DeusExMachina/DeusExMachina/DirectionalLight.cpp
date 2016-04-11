#include "DirectionalLight.hpp"

using namespace DEM;
using namespace DEM::Core;

DirectionalLight::DirectionalLight(const Math::Vector3& position, const Math::Vector3& direction)
	: Light()
{
	this->position = position;
	this->direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}