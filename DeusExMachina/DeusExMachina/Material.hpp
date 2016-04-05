#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>

#include "Asset.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

namespace DEM
{
	namespace Core
	{
		class Material : public Asset
		{
			public:
				Math::Color baseColor;

				Material(std::string vs = DEFAULT_PATH_VERTEX_SHADER, std::string fs = DEFAULT_PATH_FRAGMENT_SHADER);
				virtual ~Material();

				void bind();
				void unbind();

			protected:
				// Texture list
				Shader*		m_shaderProgram;
		};
	};
};

#endif