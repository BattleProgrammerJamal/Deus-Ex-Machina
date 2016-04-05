#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <array>

#include "Asset.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#define DEM_MAXIMUM_TEXTURES 16

namespace DEM
{
	namespace Core
	{
		class Material : public Asset
		{
			public:
				Math::Color baseColor;

				Material();
				Material(std::string vs, std::string fs);
				virtual ~Material();

				void bind();
				void unbind();

			protected:
				std::array<Texture*, DEM_MAXIMUM_TEXTURES>		m_textures;
				Shader*											m_shaderProgram;
		};
	};
};

#endif