#include "Texture.hpp"

using namespace DEM::Core;

Texture::Texture(DEM_UINT unit)
	: Asset("Texture")
{
	m_texture = 0;
	m_unit = unit;
	m_type = DEM_TEXTURE_2D;
	m_loaded = false;
}

Texture::~Texture()
{
}

void Texture::load(std::vector<std::string> paths)
{
	if (!paths.size())
	{
		return;
	}

	m_loaded = false;

	Image img;

	switch (m_type)
	{
		case DEM_TEXTURE_2D:
			m_target = GL_TEXTURE_2D;

			img.setPath(paths.at(0));
			img.load();
			glGenTextures(1, &m_texture);
			glBindTexture(m_target, m_texture);
			glTexImage2D(
				m_target,
				0, GL_RGB, 
				img.getWidth(), img.getHeight(),
				0, GL_RGB,
				GL_UNSIGNED_BYTE, img.getDatas()
			);
			glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(m_target, 0);
		break;

		case DEM_CUBEMAP:
			m_target = GL_TEXTURE_CUBE_MAP;
			
			glGenTextures(1, &m_texture);
			glBindTexture(m_target, m_texture);
			for (DEM_UINT i = 0; i < paths.size(); ++i)
			{
				img.setPath(paths.at(i));
				img.load();

				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB,
					img.getWidth(), img.getHeight(),
					0, GL_RGB,
					GL_UNSIGNED_BYTE, img.getDatas()
				);
			}
			glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(m_target, 0);
		break;
	}

	m_loaded = true;
}

GLuint Texture::getTexture() const
{
	return m_texture;
}

DEM_UINT Texture::getUnit() const
{
	return m_unit;
}

void Texture::setUnit(DEM_UINT unit)
{
	m_unit = unit;
}

DEM_TEXTURE_TYPE Texture::getType() const
{
	return m_type;
}

void Texture::setType(DEM_TEXTURE_TYPE type)
{
	m_type = type;
}

bool Texture::isLoaded() const
{
	return m_loaded;
}

void Texture::bind()
{
	glActiveTexture(m_unit);
	glBindTexture(m_target, m_texture);
}

void Texture::unbind()
{
	glBindTexture(m_target, 0);
}