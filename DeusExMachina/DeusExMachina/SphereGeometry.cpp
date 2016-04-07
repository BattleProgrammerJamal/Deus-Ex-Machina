#include "SphereGeometry.hpp"

using namespace DEM::Core;

SphereGeometry::SphereGeometry(float radius, DEM_UINT stacks, DEM_UINT slices)
	: Geometry()
{
	for (DEM_UINT i = 0; i <= stacks; ++i)
	{
		float V = i / (float)stacks;
		float phi = V * PI;

		for (DEM_UINT j = 0; j <= slices; ++j)
		{
			float U = j / (float)slices;
			float theta = U * (PI * 2.0f);

			float X = cos(theta) * sin(phi);
			float Y = cos(phi);
			float Z = sin(theta) * sin(phi);

			Vertex *vert = new Vertex(Math::Vector3(X, Y, Z) * Math::Vector3(radius, radius, radius), Math::Vector3(X, Y, Z), Math::Vector3(), Math::Vector2(U, V));

			m_vertice.push_back(vert);
		}
	}

	for (DEM_UINT i = 0; i < slices * stacks + slices; ++i)
	{
		m_indices.push_back(i);
		m_indices.push_back(i + slices + 1);
		m_indices.push_back(i + slices);

		m_indices.push_back(i + slices + 1);
		m_indices.push_back(i);
		m_indices.push_back(i + 1);
	}

	load(m_vertice, m_indices);
}