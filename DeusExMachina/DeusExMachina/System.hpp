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

#define _DEBUG 1

#ifdef _DEBUG
	#include "Benchmark.hpp"
#endif

namespace DEM
{
	namespace System
	{
		class System
		{
			public:
				static System* Instance();
				static void Destroy();

			private:
				System();
				~System();

				static System* sm_instance;
		};
	};
};

#endif