#include "Resource.hpp"

using namespace DEM::Core;

DEM_UINT Resource::sm_id = 0;

Resource::Resource()
{
	m_id = sm_id;
	++sm_id;
}

Resource::~Resource()
{
}

Resource& Resource::load()
{
	return *this;
}