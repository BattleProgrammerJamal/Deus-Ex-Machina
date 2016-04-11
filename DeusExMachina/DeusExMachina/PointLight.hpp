#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include <iostream>

#include "Math.hpp"

#include "Light.hpp"

namespace DEM
{
	namespace Core
	{
		class PointLight : public Light
		{
			public:
				Math::Vector3 position;

				PointLight(const Math::Vector3& position = Math::Vector3());
				virtual ~PointLight();

			protected:
		};
	}
};

#endif