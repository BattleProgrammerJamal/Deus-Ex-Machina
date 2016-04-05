#ifndef SHADER_HPP
#define SHADER_HPP

#define DEFAULT_PATH_VERTEX_SHADER "Assets/shaders/default.vs"
#define DEFAULT_PATH_FRAGMENT_SHADER "Assets/shaders/default.fs"

#include <iostream>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "File.hpp"
#include "Resource.hpp"

namespace DEM
{
	namespace Core
	{
		class Shader : public Resource
		{
			public:
				Shader(std::string vs = DEFAULT_PATH_VERTEX_SHADER, std::string fs = DEFAULT_PATH_FRAGMENT_SHADER);
				virtual ~Shader();

				Resource& load();

				void bind();
				void unbind();

				GLuint getProgram() const;

			protected:
				GLuint			m_program;
				std::string		m_pathVS;
				GLuint			m_vs;
				std::string		m_pathFS;
				GLuint			m_fs;
				std::string		m_pathGS;
				GLuint			m_gs;
				std::string		m_pathTS;
				GLuint			m_ts;
		};
	};
};

#endif