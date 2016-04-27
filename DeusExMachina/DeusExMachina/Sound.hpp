#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>

#include "Audio.hpp"

namespace DEM
{
	namespace Core
	{
		class Sound : public Audio
		{
			public:
				Sound();
				Sound(const std::string& path);
				virtual ~Sound();

				void load(const std::string& path);
				void play();
				void stop();
				void pause();
		};
	};
};

#endif