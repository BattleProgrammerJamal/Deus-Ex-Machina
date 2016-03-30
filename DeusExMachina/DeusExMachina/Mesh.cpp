#include "Mesh.hpp"

using namespace std;
using namespace DEM::Core;
using namespace DEM::System;

Mesh::Mesh(string name)
	: Actor(name)
{
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
}

void Mesh::Update()
{

}