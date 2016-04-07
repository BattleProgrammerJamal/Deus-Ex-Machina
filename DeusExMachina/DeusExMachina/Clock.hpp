#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <iostream>
#include <cstdint>
#include <chrono>

namespace DEM
{
	namespace System
	{
		class Clock
		{
			public:
				Clock(bool _start = false)
				{
					if (_start)
					{
						start();
					}
				}

				virtual ~Clock()
				{
				}

				void start()
				{
					_running = true;
					_currentTime = std::chrono::high_resolution_clock::now();
					_time = 0.0f;
				}

				void pause()
				{
					_running = false;
				}

				void stop()
				{
					_running = false;
					_currentTime = std::chrono::high_resolution_clock::now();
					_time = 0.0f;
				}

				void restart()
				{
					stop();
					start();
				}

				float nanoseconds()
				{
					updateClock(this);
					return _time;
				}

				float milliseconds()
				{
					updateClock(this);
					return _time / 1000000;
				}

				float seconds()
				{
					updateClock(this);
					return _time / 10000000;
				}

				bool isRunning()
				{
					return _running;
				}

			private:
				static void updateClock(Clock *clock)
				{
					if (clock->isRunning())
					{
						clock->_time = ((float)(std::chrono::high_resolution_clock::now() - clock->_currentTime).count());
					}

				}

				void setTime(float t)
				{
					_time = t;
				}

				bool _running;
				float _time;
				std::chrono::high_resolution_clock _clock;
				std::chrono::system_clock::time_point _currentTime;
		};
	};
};

#endif