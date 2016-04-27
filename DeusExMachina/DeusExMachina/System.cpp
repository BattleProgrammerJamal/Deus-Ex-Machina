#define STB_IMAGE_IMPLEMENTATION
#include "System.hpp"

using namespace DEM::System;

System* System::sm_instance = 0;

System* System::Instance()
{
	if (sm_instance == 0)
	{
		sm_instance = new System();
	}
	return sm_instance;
}

void System::Destroy()
{
	if (sm_instance)
	{
		delete sm_instance;
		sm_instance = 0;
	}
}

System::System()
{

}

System::~System()
{
}