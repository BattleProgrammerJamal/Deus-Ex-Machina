#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <iostream>
#include <vector>

#include "Audio.hpp"

namespace DEM
{
	namespace Core
	{
		class Music : public Audio
		{
			public:
				Music();
				Music(const std::string& path);
				virtual ~Music();

				void load(const std::string& path);
				void play();
				void stop();
				void pause();

				bool isPaused() const;

			protected:
				static std::vector<DEM_UINT>		sm_channels;
				FMOD_CHANNEL*						m_channel;
				bool								m_paused;
		};
	};
};

#endif