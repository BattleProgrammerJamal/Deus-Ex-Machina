#include "Material.hpp"

using namespace DEM::Core;

Material::Material()
	: Asset("Material")
{
	baseColor.set(1.0f, 1.0f, 1.0f);
	m_shaderProgram = new Shader(DEFAULT_PATH_VERTEX_SHADER, DEFAULT_PATH_FRAGMENT_SHADER);
	m_shaderProgram->load();
	for (DEM_UINT i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = new Texture(i);
	}
}

Material::Material(std::string vs, std::string fs)
	: Asset("Material")
{
	baseColor.set(1.0f, 1.0f, 1.0f);
	m_shaderProgram = new Shader(vs, fs);
	m_shaderProgram->load();
	for (DEM_UINT i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = new Texture(i);
	}
}

Material::~Material()
{
	for (Texture *tex : m_textures)
	{
		delete tex;
		tex = 0;
	}
	delete m_shaderProgram;
}

void Material::bind()
{
	m_shaderProgram->bind();
	for (Texture *tex : m_textures)
	{
		if (tex->isLoaded())
		{
			tex->bind();
		}
	}
}

void Material::unbind()
{
	for (Texture *tex : m_textures)
	{
		if (tex->isLoaded())
		{
			tex->unbind();
		}
	}
	m_shaderProgram->unbind();
}