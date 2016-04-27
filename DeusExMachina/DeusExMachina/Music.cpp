#include "Music.hpp"

using namespace DEM::Core;

std::vector<DEM_UINT> Music::sm_channels = std::vector<DEM_UINT>();

Music::Music()
	: Audio()
{
	m_paused = false;
	if (sm_channels.size() == 0)
	{
		sm_channels.emplace_back(0);
	}
	else
	{
		sm_channels.emplace_back(sm_channels.at(sm_channels.size() - 1) + 1);
	}
	FMOD_System_GetChannel(sm_system, sm_channels.at(sm_channels.size() - 1), &m_channel);
}

Music::Music(const std::string& path)
	: Audio(path)
{
	m_paused = false;
	if (sm_channels.size() == 0)
	{
		sm_channels.emplace_back(0);
	}
	else
	{
		sm_channels.emplace_back(sm_channels.at(sm_channels.size() - 1) + 1);
	}
	FMOD_System_GetChannel(sm_system, sm_channels.at(sm_channels.size() - 1), &m_channel);
}

Music::~Music()
{
	if (m_source != 0)
	{
		FMOD_Sound_Release(m_source);
	}
}

void Music::load(const std::string& path)
{
	m_loaded = false;

	//FMOD_System_CreateSound(sm_system, path.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_source);
	FMOD_System_CreateSound(sm_system, path.c_str(), FMOD_LOOP_NORMAL , 0, &m_source);

	FMOD_Sound_SetLoopCount(m_source, -1);

	m_loaded = true;
}

void Music::play()
{
	if (m_loaded)
	{
		if (m_paused) { FMOD_Channel_SetPaused(m_channel, 0); m_paused = false; }
		FMOD_System_PlaySound(sm_system, FMOD_CHANNEL_FREE, m_source, 0, 0);
	}
}

void Music::stop()
{
	if (m_loaded)
	{
		if (m_paused) { FMOD_Channel_SetPaused(m_channel, 0); m_paused = false; }
		FMOD_Channel_Stop(m_channel);
	}
}

void Music::pause()
{
	if (m_loaded)
	{
		m_paused = true;
		FMOD_Channel_SetPaused(m_channel, 1);
	}
}

bool Music::isPaused() const
{
	return m_paused;
}