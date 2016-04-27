#include "Profiler.hpp"

using namespace DEM::System;

Clock Profiler::sm_clock = Clock();

PROFILER_TIME_UNIT Profiler::unit = SECONDS;