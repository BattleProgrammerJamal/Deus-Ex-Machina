#include "PhongMaterial.hpp"

using namespace DEM;
using namespace DEM::Core;

PhongMaterial::PhongMaterial(Math::Color _ambient, Math::Color _diffuse, Math::Color _specular, float _shininess)
	: Material("Assets/shaders/phong.vs", "Assets/shaders/phong.fs")
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::updateParameters()
{
	GLuint ambientLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.ambient");
	glUniform3f(ambientLocation, ambient.r, ambient.g, ambient.b);

	GLuint diffuseLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.diffuse");
	glUniform3f(diffuseLocation, diffuse.r, diffuse.g, diffuse.b);

	GLuint specularLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.specular");
	glUniform3f(specularLocation, specular.r, specular.g, specular.b);

	GLuint shininessLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.shininess");
	glUniform1f(shininessLocation, shininess);
}