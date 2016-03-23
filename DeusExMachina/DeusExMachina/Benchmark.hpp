#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <iostream>
#include "Clock.hpp"

namespace DEM
{
	namespace System
	{
		class Benchmark
		{
			public:
				void Begin()
				{
					m_clock.start();
				}

				float End()
				{
					float rslt = m_clock.seconds();
					m_clock.stop();
					return rslt;
				}

			private:
				Clock m_clock;
		};
	};
};

#endif