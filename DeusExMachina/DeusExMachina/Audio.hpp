#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <iostream>

#include "fmod.hpp"

#include "Actor.hpp"

#define DEM_MAXIMUM_SIMULTANEOUS_CHANNELS 32

namespace DEM
{
	namespace Core
	{
		class Audio : public Actor
		{
			public:
				Audio();
				Audio(const std::string& path);
				virtual ~Audio();

				void Render();
				void Update();

				bool isLoaded() const;

				virtual void load(const std::string& path){};
				virtual void play() = 0;
				virtual void stop() = 0;
				virtual void pause() = 0;

			protected:
				bool					m_loaded;
				static FMOD_SYSTEM*		sm_system;
				FMOD_SOUND*				m_source;
		};
	};
};

#endif