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

	GLuint programID = m_shaderProgram->getProgram();

	DEM_UINT index = 0;
	for (Texture *tex : m_textures)
	{
		if (tex->isLoaded())
		{
			tex->bind();
			std::strstream stream;
			stream << "u_texture" << index << '\0';
			GLuint textureLocation = glGetUniformLocation(programID, stream.str());
			glUniform1i(textureLocation, tex->getUnit());
		}
		++index;
	}

	for (ShaderUniform *uniform : uniforms)
	{
		GLuint uniformLocation = glGetUniformLocation(programID, uniform->name.c_str());
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
		if (typeid(*uniform->value) == typeid(ShaderUQuaternion))
		{
			Math::Quaternion value = (static_cast<ShaderUQuaternion*>(uniform->value))->get();
			glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
		}
		if (typeid(*uniform->value) == typeid(ShaderUMat3))
		{
			glm::mat3 value = static_cast<ShaderUMat3*>(uniform->value)->get();
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
		}
		if (typeid(*uniform->value) == typeid(ShaderUMat4))
		{
			glm::mat4 value = static_cast<ShaderUMat4*>(uniform->value)->get();
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
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

Material& Material::loadTexture(const std::string path)
{
	static DEM_UINT index = 0;

	std::vector<std::string> realpath;
	realpath.emplace_back(path);
	m_textures[index]->load(realpath);

	index = (index + 1) % DEM_MAXIMUM_TEXTURES;
	return *this;
}

Texture* Material::operator[](DEM_UINT index)
{
	if (index < m_textures.size())
	{
		return m_textures.at(index);
	}
	return 0;
}