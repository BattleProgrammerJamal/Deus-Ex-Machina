#include "Material.hpp"

using namespace DEM::Core;

Material::Material()
	: Asset("Material")
{
	baseColor.set(1.0f, 1.0f, 1.0f, 1.0f);
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
	baseColor.set(1.0f, 1.0f, 1.0f, 1.0f);
	m_shaderProgram = new Shader(vs, fs);
	m_shaderProgram->load();
	for (DEM_UINT i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = new Texture(i);
	}
}

Material::Material(const Material& material)
	: Asset("Material")
{
	m_shaderProgram = material.m_shaderProgram;
	baseColor = Math::Color(material.baseColor);
	for (DEM_UINT i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = material.m_textures.at(i);
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

	for (ShaderUniform *uniform : uniforms)
	{
		GLuint uniformLocation = glGetUniformLocation(m_shaderProgram->getProgram(), uniform->name.c_str());
		if (typeid(*uniform->value) == typeid(ShaderUInt))
		{
			ShaderUInt *value = static_cast<ShaderUInt*>(uniform->value);
			glUniform1i(uniformLocation, value->get());
		}
		if (typeid(*uniform->value) == typeid(ShaderUFloat))
		{
			ShaderUFloat *value = static_cast<ShaderUFloat*>(uniform->value);
			glUniform1f(uniformLocation, value->get());
		}
		if (typeid(*uniform->value) == typeid(ShaderUFloat2))
		{
			Math::Vector2 value = (static_cast<ShaderUFloat2*>(uniform->value))->get();
			glUniform2f(uniformLocation, value.x, value.y);
		}
		if (typeid(*uniform->value) == typeid(ShaderUFloat3))
		{
			Math::Vector3 value = (static_cast<ShaderUFloat3*>(uniform->value))->get();
			glUniform3f(uniformLocation, value.x, value.y, value.z);
		}
		if (typeid(*uniform->value) == typeid(ShaderUMat))
		{
			Math::Matrix<float> value = static_cast<ShaderUMat*>(uniform->value)->get();
			if (value.size() == 16)
			{
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value.ptr_value());
			}
			else
			{
				glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, value.ptr_value());
			}
		}
	}

	updateParameters();
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

void Material::updateParameters()
{
	GLuint baseColorLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_material.color");
	glUniform3f(baseColorLocation, baseColor.r, baseColor.g, baseColor.b);
}

Shader* Material::getShaderProgram() const
{
	return m_shaderProgram;
}

void Material::setShaderProgram(Shader *shader)
{
	m_shaderProgram = shader;
}