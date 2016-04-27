#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include <iostream>

#include "Math.hpp"

#include "Light.hpp"

namespace DEM
{
	namespace Core
	{
		struct LightAttenuation
		{
			float	constant;
			float	linear;
			float	quadric;

			LightAttenuation()
			{
				this->constant = 1.0f;
				this->linear = 0.14f;
				this->quadric = 0.07f;
			}

			LightAttenuation(float constant, float linear, float quadric)
			{
				this->constant = constant;
				this->linear = linear;
				this->quadric = quadric;
			}
		};

		class PointLight : public Light
		{
			public:
				Math::Vector3		position;
				LightAttenuation	attenuation;

				PointLight(const Math::Vector3& position = Math::Vector3());
				virtual ~PointLight();

			protected:
		};
	}
};

#endif