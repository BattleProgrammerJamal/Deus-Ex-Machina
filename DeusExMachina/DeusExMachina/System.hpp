#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>

#include "Crypto.hpp"
#include "Collections.hpp"
#include "Clock.hpp"
#include "Math.hpp"
#include "Profiler.hpp"
#include "Resource.hpp"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 3

namespace DEM
{
	namespace System
	{
		class System
		{
			public:
				static System* Instance();
				static void Destroy();

				virtual void initAudioAPI();
				virtual void initUiAPI();

			private:
				System();
				~System();

				static System* sm_instance;
		};
	};
};

#endif