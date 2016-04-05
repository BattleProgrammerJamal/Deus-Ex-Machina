#include "Asset.hpp"

using namespace DEM::Core;

DEM_UINT Asset::sm_id = 0;

Asset::Asset(const std::string& name)
{
	m_id = sm_id;
	++sm_id;
	m_name = name;
}

Asset::~Asset()
{
}

std::string Asset::getName() const
{
	return m_name;
}

void Asset::setName(const std::string& name)
{
	m_name = name;
}