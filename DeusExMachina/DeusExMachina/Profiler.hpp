#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <iostream>
#include "Clock.hpp"

namespace DEM
{
	namespace System
	{
		class Profiler
		{
			public:
				static void Begin()
				{
					sm_clock.start();
				}

				static float End()
				{
					float rslt = sm_clock.seconds();
					sm_clock.stop();
					return rslt;
				}

			private:
				static Clock sm_clock;
		};
	};
};

#endif