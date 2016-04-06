#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Math.hpp"
#include "Asset.hpp"

#define BUFFER_OFFSET(idx) (void*)(sizeof(float) * idx)

namespace DEM
{
	namespace Core
	{
		struct Vertex
		{
			static const GLsizei stride = static_cast<GLsizei>(sizeof(float) * 11);

			Math::Vector3 position;
			Math::Vector3 normal;
			Math::Vector3 tangent;
			Math::Vector2 uv;

			Vertex(Math::Vector3 _position = Math::Vector3(), Math::Vector3 _normal = Math::Vector3(), Math::Vector3 _tangent = Math::Vector3(), Math::Vector2 _uv = Math::Vector2())
			{
				position = _position;
				normal = _normal;
				tangent = _tangent;
				uv = _uv;
			}
		};

		class Geometry : public Asset
		{
			public:
				Geometry();
				Geometry(std::vector<Vertex*> vertice, std::vector<GLuint> indices);
				Geometry(const Geometry& geometry);
				virtual ~Geometry();

				void load(std::vector<Vertex*> vertice, std::vector<GLuint> indices);

				void bind();
				void unbind();

				std::vector<Vertex*> getVertice() const;
				void setVertice(std::vector<Vertex*> vertice);

				std::vector<GLuint> getIndices() const;
				void setIndices(std::vector<GLuint> indices);

				GLuint getVAO() const;

				GLuint getVBO() const;

				GLuint getIBO() const;

			protected:
				std::vector<Vertex*>	m_vertice;
				std::vector<GLuint>		m_indices;
				GLuint					m_vao;
				GLuint					m_vbo;
				GLuint					m_ibo;
		};
	};
};

#endif