#define STB_IMAGE_IMPLEMENTATION
#include "Image.hpp"

using namespace DEM::Core;

Image::Image(const std::string& path)
	: Resource()
{
	m_data = 0;
	m_width = 0;
	m_height = 0;
	m_comp = 0;
	m_path = path;
	m_loaded = false;
}

Image::~Image()
{
	free(m_data);
}

Resource& Image::load()
{
	m_loaded = false;

	m_data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_comp, 0);
	
	if (m_data)
	{
		m_loaded = true;
	}
	return *this;
}

DEM_UCHAR* Image::getDatas() const
{
	return m_data;
}

int Image::getWidth() const
{
	return m_width;
}

int Image::getHeight() const
{
	return m_height;
}

int Image::getComp() const
{
	return m_comp;
}

std::string Image::getPath() const
{
	return m_path;
}
void Image::setPath(const std::string& path)
{
	m_path = path;
}

bool Image::isLoaded() const
{
	return m_loaded;
}