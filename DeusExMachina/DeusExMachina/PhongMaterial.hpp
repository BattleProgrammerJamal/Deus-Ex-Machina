#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP

#include <iostream>

#include "Math.hpp"
#include "Color.hpp"
#include "Material.hpp"

namespace DEM
{
	namespace Core
	{
		class PhongMaterial : public Material
		{
			public:
				Math::Color ambient;
				Math::Color diffuse;
				Math::Color specular;
				float shininess;

				PhongMaterial(Math::Color _ambient, Math::Color _diffuse, Math::Color _specular, float _shininess);
				~PhongMaterial();

				void updateParameters();

			private:
		};
	};
};

#endif