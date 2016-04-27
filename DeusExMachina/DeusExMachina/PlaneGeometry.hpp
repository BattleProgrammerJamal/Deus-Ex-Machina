#ifndef PLANE_GEOMETRY_HPP
#define PLANE_GEOMETRY_HPP

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
		class PlaneGeometry : public Geometry
		{
			public:
				PlaneGeometry(DEM_UINT l = 1, DEM_UINT c = 1, float width = 1.0f, float height = 1.0f);

			protected:
		};
	};
};

#endif