#include "DEM.hpp"

using namespace DEM;

DeusExMachina* DeusExMachina::sm_instance = 0;

DeusExMachina::DeusExMachina()
{
	m_system = System::System::Instance();
}

DeusExMachina::~DeusExMachina()
{
}

DeusExMachina* DeusExMachina::Instance()
{
	if (sm_instance == 0)
	{
		sm_instance = new DeusExMachina();
	}

	return sm_instance;
}

void DeusExMachina::Destroy()
{
	if (sm_instance)
	{
		delete sm_instance;
	}
}

System::System* DeusExMachina::getSystem() const
{
	return m_system;
}