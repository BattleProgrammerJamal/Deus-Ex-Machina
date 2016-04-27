#include "Sound.hpp"

using namespace DEM::Core;

Sound::Sound()
	: Audio()
{
}

Sound::Sound(const std::string& path)
	: Audio(path)
{
}

Sound::~Sound()
{
	if (m_source != 0)
	{
		FMOD_Sound_Release(m_source);
	}
}

void Sound::load(const std::string& path)
{
	m_loaded = false;

	FMOD_System_CreateSound(sm_system, path.c_str(), FMOD_CREATESAMPLE, 0, &m_source);

	m_loaded = true;
}

void Sound::play()
{
	if (m_loaded)
	{
		FMOD_System_PlaySound(sm_system, FMOD_CHANNEL_FREE, m_source, 0, 0);
	}
}

void Sound::stop()
{
}

void Sound::pause()
{
}