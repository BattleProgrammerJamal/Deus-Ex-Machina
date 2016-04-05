#include "Mesh.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;
using namespace DEM::Math;

DEM_UINT Mesh::sm_id = 0;
Clock* Mesh::clock = new Clock();

Mesh::Mesh(Geometry *geometry, Material *material, string name)
	: Actor(name)
{
	m_id = sm_id;
	++sm_id;
	m_geometry = geometry;
	m_material = material;
	clock->start();
}

Mesh::~Mesh()
{
	delete m_geometry;
	delete m_material;
}

void Mesh::Render()
{
	float t = clock->seconds();

	glRotatef(0.05f, 0.0f, 1.0f, 0.0f);

	static float theta = 0.0f;
	static float phi = 0.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (DEM_UINT i = 0; i < 64; ++i)
		{
			for (DEM_UINT j = 0; j < 64; ++j)
			{
				theta = 2.0f * PI * i / 64;
				phi = PI * j / 64;

				glVertex3f(
					0.5f * sin(phi) * (float)cos(i&j),
					0.5f * cos(theta*(((int)phi)&(int)t)) * (float)sin(i << j&(int)t),
					0.5f * sin(theta - phi * t)
				);
			}
		}
	glEnd();
}

void Mesh::Update()
{
}

Geometry* Mesh::getGeometry() const
{
	return m_geometry;
}

void Mesh::setGeometry(Geometry* geometry)
{
	m_geometry = geometry;
}

Material* Mesh::getMaterial() const
{
	return m_material;
}

void Mesh::setMaterial(Material* material)
{
	m_material = material;
}