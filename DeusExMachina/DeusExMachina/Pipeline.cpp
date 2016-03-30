#include "Pipeline.hpp"

using namespace DEM::Core;

DEM_UINT Pipeline::sm_id = 0;

std::vector<Pipeline*> Pipeline::sm_pipelines = std::vector<Pipeline*>();

Pipeline::Pipeline()
{
	sm_pipelines.push_back(this);
	m_id = sm_id;
	++sm_id;
	setState(true);
}

void Pipeline::operator()()
{
}

void Pipeline::create()
{
	m_proc = new std::thread(&Pipeline::operator(), this);
}

void Pipeline::run()
{
	m_proc->join();
}

DEM_UINT Pipeline::getId() const { return m_id; }

bool Pipeline::state() const
{
	return m_running.load(std::memory_order::memory_order_acquire);
}

void Pipeline::setState(bool state)
{
	m_running.store(state, std::memory_order::memory_order_release);
}

void Pipeline::command(PIPELINE_SIG sig)
{
	switch (sig)
	{
		case KILL_ALL:
			for (DEM_UINT i = 0; i < sm_pipelines.size(); ++i)
			{
				if (sm_pipelines.at(i))
				{
					sm_pipelines.at(i)->setState(false);
				}
			}
		break;
	}
}