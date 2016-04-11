#include "PointLight.hpp"

using namespace DEM;
using namespace DEM::Core;

PointLight::PointLight(const Math::Vector3& position)
	: Light()
{
	this->position = position;
}

PointLight::~PointLight()
{

}