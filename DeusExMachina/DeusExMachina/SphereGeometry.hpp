#ifndef SPHERE_GEOMETRY_HPP
#define SPHERE_GEOMETRY_HPP

#include <iostream>
#include <vector>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Geometry.hpp"

namespace DEM
{
	namespace Core
	{
		class SphereGeometry : public Geometry
		{
			public:
				SphereGeometry(float radius, DEM_UINT stacks, DEM_UINT slices);

			protected:
		};
	};
};

#endif