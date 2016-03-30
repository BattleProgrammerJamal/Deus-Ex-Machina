#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

#include "Types.hpp"

namespace DEM
{
	namespace Core
	{
		enum PIPELINE_SIG {
			KILL_ALL = 0
		};

		class Pipeline
		{
			public:
				Pipeline();

				virtual void operator()();

				virtual void create();
				virtual void run();

				DEM_UINT getId() const;

				bool state() const;
				void setState(bool state);

				static void command(PIPELINE_SIG sig);

			protected:
				std::thread*						m_proc;
				static DEM_UINT						sm_id;
				DEM_UINT							m_id;
				std::atomic<bool>					m_running;

			private:
				static std::vector<Pipeline*>		sm_pipelines;
		};
	};
};

#endif