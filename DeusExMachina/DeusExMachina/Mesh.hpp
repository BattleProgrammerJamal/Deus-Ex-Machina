#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <STB/stb_image.h>

#include "Math.hpp"
#include "Color.hpp"
#include "Geometry.hpp"
#include "Material.hpp"
#include "Actor.hpp"
#include "Clock.hpp"
#include "DEM.hpp"

namespace DEM
{
	namespace Core
	{
		class Mesh : public Actor
		{
			public:
				std::vector<GLuint> drawStyles;
				bool wireframe;
				DEM::Math::Color wireframeStyle;

				Mesh(Geometry *geometry, Material *material, std::string name = "Actor");
				Mesh(const Mesh& mesh);
				~Mesh();

				Geometry* getGeometry() const;
				void setGeometry(Geometry* geometry);
				Material* getMaterial() const;
				void setMaterial(Material* material);

				static System::Clock* getClock();
				
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