#include "Geometry.hpp"

using namespace DEM::Core;

Geometry::Geometry()
	: Asset("Geometry")
{
	m_vao = 0;
	m_vbo = 0;
	m_ibo = 0;
}

Geometry::Geometry(std::vector<Vertex*> vertice, std::vector<GLuint> indices)
	: Asset("Geometry")
{
	m_vao = 0;
	m_vbo = 0;
	m_ibo = 0;
	load(vertice, indices);
}

Geometry::Geometry(const Geometry& geometry)
	: Asset("Geometry")
{
	m_vao = geometry.m_vao;
	m_vbo = geometry.m_vbo;
	m_ibo = geometry.m_ibo;
	load(geometry.m_vertice, geometry.m_indices);
}

Geometry::~Geometry()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_vao);
}

void Geometry::load(std::vector<Vertex*> vertice, std::vector<GLuint> indices)
{
	m_vertice = vertice;
	m_indices = indices;

	std::vector<float> verticeFlat;
	for (DEM_UINT i = 0; i < m_vertice.size(); ++i)
	{
		verticeFlat.push_back(m_vertice.at(i)->position.x);
		verticeFlat.push_back(m_vertice.at(i)->position.y);
		verticeFlat.push_back(m_vertice.at(i)->position.z);

		verticeFlat.push_back(m_vertice.at(i)->normal.x);
		verticeFlat.push_back(m_vertice.at(i)->normal.y);
		verticeFlat.push_back(m_vertice.at(i)->normal.z);

		verticeFlat.push_back(m_vertice.at(i)->tangent.x);
		verticeFlat.push_back(m_vertice.at(i)->tangent.y);
		verticeFlat.push_back(m_vertice.at(i)->tangent.z);

		verticeFlat.push_back(m_vertice.at(i)->uv.x);
		verticeFlat.push_back(m_vertice.at(i)->uv.y);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticeFlat.size(), (const void*)&verticeFlat[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(9));

	glBindVertexArray(0);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_indices.size(), (const void*)&m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::bind()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Geometry::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

std::vector<Vertex*> Geometry::getVertice() const
{
	return m_vertice;
}
void Geometry::setVertice(std::vector<Vertex*> vertice)
{
	m_vertice = vertice;
}

std::vector<GLuint> Geometry::getIndices() const
{
	return m_indices;
}
void Geometry::setIndices(std::vector<GLuint> indices)
{
	m_indices = indices;
}

GLuint Geometry::getVAO() const
{
	return m_vao;
}

GLuint Geometry::getVBO() const
{
	return m_vbo;
}

GLuint Geometry::getIBO() const
{
	return m_ibo;
}