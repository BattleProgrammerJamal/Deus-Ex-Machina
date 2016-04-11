#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <vector>

#include "Math.hpp"
#include "Color.hpp"
#include "Actor.hpp"

namespace DEM
{
	namespace Core
	{
		class Light : public Actor
		{
			public:
				Math::Color color;
				float intensity;

				Light();
				virtual ~Light();

				static std::vector<Light*> getLights();

			protected:
				void _dynamicReserve();

				static std::vector<Light*> sm_lights;
		};
	}
};

#endif