#include "MorphTargetGeometry.hpp"

using namespace DEM::Core;

MorphTargetGeometry::MorphTargetGeometry(Geometry *base, std::vector<MorphTarget*> morphTargets)
	: Geometry()
{
	m_baseGeometry = base;
	m_morphTargets = morphTargets;
	load();
}

void MorphTargetGeometry::load()
{
	m_vertice = m_baseGeometry->getVertice();
	m_indices = m_baseGeometry->getIndices();

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

		for (DEM_UINT j = 0; j < m_morphTargets.size(); ++j)
		{
			Math::Vector3 mtPosition = m_morphTargets.at(j)->geometry->getVertice().at(i)->position;
			verticeFlat.push_back(mtPosition.x);
			verticeFlat.push_back(mtPosition.y);
			verticeFlat.push_back(mtPosition.z);
		}
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* verticeFlat.size(), (const void*)&verticeFlat[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	for (DEM_UINT j = 0; j < m_morphTargets.size(); ++j)
	{
		glEnableVertexAttribArray(4 + j);
	}

	GLsizei stride = static_cast<GLsizei>(sizeof(float)* (11 + m_morphTargets.size() * 3));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(9));

	for (DEM_UINT j = 0; j < m_morphTargets.size(); ++j)
	{
		GLuint index = 4 + j;
		GLuint offset = 11 + 3 * j;
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(offset));
	}

	glBindVertexArray(0);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_indices.size(), (const void*)&m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MorphTargetGeometry& MorphTargetGeometry::addMorphTarget(MorphTarget *morphTarget)
{
	m_morphTargets.emplace_back(morphTarget);
	return *this;
}

std::vector<MorphTarget*> MorphTargetGeometry::getMorphTargets() const
{
	return m_morphTargets;
}