#include "PlaneGeometry.hpp"

using namespace DEM::Core;

PlaneGeometry::PlaneGeometry(DEM_UINT l, DEM_UINT c, float width, float height)
	: Geometry()
{
	for (DEM_UINT i = 0; i <= l; ++i)
	{
		float V = i / (float)l;

		for (DEM_UINT j = 0; j <= c; ++j)
		{
			float U = j / (float)c;

			float X = U;
			float Y = 0.0f;
			float Z = V;

			Vertex *vert = new Vertex(Math::Vector3(X * width, Y, Z * height), Math::Vector3(X, Y, Z), Math::Vector3(), Math::Vector2(U, V));

			m_vertice.push_back(vert);
		}
	}

	for (DEM_UINT i = 0; i < c * l + c; ++i)
	{
		m_indices.push_back(i);
		m_indices.push_back(i + c + 1);
		m_indices.push_back(i + c);

		m_indices.push_back(i + c + 1);
		m_indices.push_back(i);
		m_indices.push_back(i + 1);
	}

	load(m_vertice, m_indices);
}