#include "Material.hpp"

using namespace DEM::Core;

Material::Material(std::string vs, std::string fs)
	: Asset("Material")
{
	baseColor.set(1.0f, 1.0f, 1.0f);
	m_shaderProgram = new Shader(vs, fs);
}

Material::~Material()
{

}

void Material::bind()
{

}

void Material::unbind()
{

}