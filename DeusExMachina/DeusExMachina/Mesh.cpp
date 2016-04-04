#include "Mesh.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;

Mesh::Mesh(string name)
	: Actor(name)
{
	clock.start();
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	float t = clock.seconds();

	glRotatef(0.05f, 0.0f, 1.0f, 0.0f);

	static float theta = 0.0f;
	static float phi = 0.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (DEM_UINT i = 0; i < 64; ++i)
		{
			for (DEM_UINT j = 0; j < 64; ++j)
			{
				theta = 2.0f * PI * i / 64;
				phi = PI * j / 64;

				glVertex3f(
					0.5f * cos(theta) * sin(phi),
					0.5f * sin(theta) * sin(phi),
					0.5f * cos(phi)
				);
			}
		}
	glEnd();
}

void Mesh::Update()
{

}