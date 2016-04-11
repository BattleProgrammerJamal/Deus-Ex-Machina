#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include <iostream>

#include "Math.hpp"

#include "Light.hpp"

namespace DEM
{
	namespace Core
	{
		class DirectionalLight : public Light
		{
			public:
				Math::Vector3 position;
				Math::Vector3 direction;

				DirectionalLight(const Math::Vector3& position = Math::Vector3(), const Math::Vector3& direction = Math::Vector3());
				virtual ~DirectionalLight();

			protected:
		};
	}
};

#endif