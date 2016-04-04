#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include <gl/glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <STB/stb_image.h>

#include "Math.hpp"

#include "Actor.hpp"

#include "Clock.hpp"

namespace DEM
{
	namespace Core
	{
		class Mesh : public Actor
		{
			public:
				Mesh(std::string name = "Actor");
				~Mesh();
				
				void Render();

				void Update();

			protected:
				System::Clock clock;
		};
	};
};

#endif