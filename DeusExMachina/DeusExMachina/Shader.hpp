#ifndef SHADER_HPP
#define SHADER_HPP

#define DEFAULT_PATH_VERTEX_SHADER "Assets/shaders/default.vs"
#define DEFAULT_PATH_FRAGMENT_SHADER "Assets/shaders/default.fs"

#include <iostream>

namespace DEM
{
	namespace Core
	{
		class Shader
		{
			public:
				Shader(std::string vs, std::string fs);
				virtual ~Shader();

			protected:

		};
	};
};

#endif