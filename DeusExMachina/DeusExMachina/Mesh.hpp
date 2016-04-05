#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <STB/stb_image.h>

#include "Math.hpp"
#include "Geometry.hpp"
#include "Material.hpp"
#include "Actor.hpp"
#include "Clock.hpp"

namespace DEM
{
	namespace Core
	{
		class Mesh : public Actor
		{
			public:
				Mesh(Geometry *geometry, Material *material, std::string name = "Actor");
				~Mesh();

				Geometry* getGeometry() const;
				void setGeometry(Geometry* geometry);
				Material* getMaterial() const;
				void setMaterial(Material* material);
				
				void Render();

				void Update();

			protected:
				static System::Clock*	clock;
				static DEM_UINT			sm_id;
				DEM_UINT				m_id;
				Geometry*				m_geometry;
				Material*				m_material;
		};
	};
};

#endif