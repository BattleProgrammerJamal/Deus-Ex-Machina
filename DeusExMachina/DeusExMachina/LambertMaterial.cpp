#include "LambertMaterial.hpp"

using namespace DEM;
using namespace DEM::Core;

LambertMaterial::LambertMaterial(Math::Color _ambient, Math::Color _diffuse)
	: Material("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs")
{
	ambient = _ambient;
	diffuse = _diffuse;
}

LambertMaterial::~LambertMaterial()
{
}

void LambertMaterial::updateParameters()
{
	GLuint ambientLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.ambient");
	glUniform3f(ambientLocation, ambient.r, ambient.g, ambient.b);

	GLuint diffuseLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.diffuse");
	glUniform3f(diffuseLocation, diffuse.r, diffuse.g, diffuse.b);
}