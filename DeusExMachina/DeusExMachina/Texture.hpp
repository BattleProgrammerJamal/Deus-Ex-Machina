#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <vector>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Asset.hpp"
#include "Image.hpp"

namespace DEM
{
	namespace Core
	{
		enum DEM_TEXTURE_TYPE
		{
			DEM_TEXTURE_2D,
			DEM_CUBEMAP
		};

		class Texture : public Asset
		{
			public:
				Texture(DEM_UINT unit);
				virtual ~Texture();

				void load(std::vector<std::string> paths);

				GLuint getTexture() const;

				DEM_UINT getUnit() const;
				void setUnit(DEM_UINT unit);

				DEM_TEXTURE_TYPE getType() const;
				void setType(DEM_TEXTURE_TYPE type);

				void bind();
				void unbind();

			private:
				DEM_TEXTURE_TYPE	m_type;
				GLuint				m_target;
				GLuint				m_texture;
				DEM_UINT			m_unit;
		};
	};
};

#endif