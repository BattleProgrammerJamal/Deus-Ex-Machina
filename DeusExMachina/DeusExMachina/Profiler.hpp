#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <iostream>
#include "Clock.hpp"

namespace DEM
{
	namespace System
	{
		enum PROFILER_TIME_UNIT
		{
			MILLISECONDS = 0,
			SECONDS
		};

		class Profiler
		{
			public:
				static PROFILER_TIME_UNIT unit;

				static void Begin()
				{
					sm_clock.start();
				}

				static float End()
				{
					float rslt = 0.0f;
					switch (unit)
					{
						case MILLISECONDS:
							rslt = sm_clock.milliseconds();
						break;

						case SECONDS:
							rslt = sm_clock.seconds();
						break;

						default:
							rslt = sm_clock.seconds();
						break;
					}
					sm_clock.stop();
					return rslt;
				}

			private:
				static Clock sm_clock;
		};
	};
};

#endif