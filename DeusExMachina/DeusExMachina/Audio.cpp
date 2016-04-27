#include "Audio.hpp"

using namespace DEM::Core;

FMOD_SYSTEM* Audio::sm_system = 0;

Audio::Audio()
	: Actor("Audio")
{
	m_loaded = false;

	if (sm_system == 0)
	{
		FMOD_System_Create(&sm_system);
		FMOD_System_Init(sm_system, DEM_MAXIMUM_SIMULTANEOUS_CHANNELS, FMOD_INIT_NORMAL, (void*)0);
	}
}

Audio::Audio(const std::string& path)
	: Actor("Audio")
{
	m_loaded = false;
}

Audio::~Audio()
{
	if (sm_system)
	{
		FMOD_System_Close(sm_system);
		FMOD_System_Release(sm_system);
	}
}

void Audio::Render()
{
}

void Audio::Update()
{
}

bool Audio::isLoaded() const
{
	return m_loaded;
}