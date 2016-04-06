#ifndef LAMBERT_MATERIAL_HPP
#define LAMBERT_MATERIAL_HPP

#include <iostream>

#include "Math.hpp"
#include "Color.hpp"
#include "Material.hpp"

namespace DEM
{
	namespace Core
	{
		class LambertMaterial : public Material
		{
			public:
				Math::Color ambient;
				Math::Color diffuse;

				LambertMaterial(Math::Color _ambient, Math::Color _diffuse);
				~LambertMaterial();

				void updateParameters();

			private:
		};
	};
};

#endif