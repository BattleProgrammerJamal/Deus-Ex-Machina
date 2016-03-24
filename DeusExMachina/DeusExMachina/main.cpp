#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;

#include <vector>
#include <ctime>

struct Particle
{
	public:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;
		Vector3 force;
		Vector3 oldPosition;
		float friction;
		float mass;
		DEM_UINT id;

		Particle(Vector3 _position = Vector3(0.0f, 0.0f, 0.0f), float _friction = 0.5f)
		{
			id = Particle::sm_id;
			++Particle::sm_id;
			position = _position;
			friction = _friction;
			mass = 1.0f;
		}

		virtual ~Particle()
		{
		}

		void update(float deltaTime)
		{
			velocity = position - oldPosition;
			acceleration = force / mass;

			position = position + velocity + acceleration * IG; 

			oldPosition = Vector3(position);
			force = force * friction;
		}

		void addForce(Vector3 _force)
		{
			force += _force;
		}

		friend ostream& operator<<(ostream& out, const Particle& p);

	private:
		static float IG;
		static DEM_UINT sm_id;
};

float Particle::IG = 1.0f / -9.81f;
DEM_UINT Particle::sm_id = 0;

ostream& ::operator<<(ostream& out, const Particle& p)
{
	out << "Particle <" << p.id << "> :" << endl << "\tposition = " << p.position << endl <<
		"\tvelocity = " << p.velocity << endl <<
		"\tacceleration = " << p.acceleration << endl <<
		"\tforce = " << p.force << endl <<
		"\tfriction = " << p.friction << endl <<
		"\tmass = " << p.mass << endl <<
		"\toldPosition = " << p.oldPosition << endl <<
		endl;
	return out;
}

struct ParticlePool
{
	public:
		thread *poolThread;
		vector<Particle*> particles;
		Clock _clock;
		std::atomic<bool> running;

		ParticlePool(vector<Particle*> _particles)
		{
			particles = _particles;
			_clock.start();
			poolThread = new thread(_run, this);
			running.store(false, memory_order::memory_order_relaxed);
		}

		virtual ~ParticlePool()
		{
			delete poolThread;
			for (Particle *p : particles)
			{
				delete p;
			}
		}

		void operator()()
		{
			if (poolThread->joinable() && !running.load(memory_order::memory_order_acquire))
			{
				running.store(true, memory_order::memory_order_relaxed);
				poolThread->join();
			}
		}

	private:
		static void _run(ParticlePool *pool)
		{
			for (Particle *p : pool->particles)
			{
				cout << "Update Particle<" << p->id << "> New Position : " << p->position << endl;
				p->update(pool->_clock.milliseconds());
			}
			pool->running.store(false, memory_order::memory_order_relaxed);
		}
};

template <DEM_UINT particleCount>
struct ParticleFlow
{
	public:
		ParticleFlow()
		{
			srand(time(0));

			maxThreads = thread::hardware_concurrency();

			DEM_UINT threadParticleStride = particleCount / maxThreads;

			cout << "\tParticleFlow Created !" << endl;
			cout << " > " << maxThreads << " simultaneaous threads" << endl;
			cout << " > " << particleCount << " particles" << endl;
			cout << " > " << threadParticleStride << " particles per thread" << endl << endl;

			for (DEM_UINT i = 0; i < maxThreads; ++i)
			{
				vector<Particle*> particles;
				for (DEM_UINT j = 0; j < threadParticleStride; ++j)
				{
					Particle *p = new Particle(Vector3(
						cos((float)(rand() % 15)) * 20,
						sin((float)(rand() % 15)) * 20,
						cos((float)(rand() % 10)) * 20
					));
					p->addForce(Vector3(
						cos((float)(rand() % 15)) * 50,
						sin((float)(rand() % 15)) * 50,
						cos((float)(rand() % 10)) * 50
					));
					p->mass = 1.0f + cos((float)(rand() % 15)) * 5;
					particles.push_back(p);
					allParticles.push_back(p);
				}
				ParticlePool *pool = new ParticlePool(particles);
				particlePools.push_back(pool);
			}
		}

		virtual ~ParticleFlow()
		{
			for (ParticlePool *pool : particlePools)
			{
				delete pool;
			}
		}

		void update()
		{
			bool somePoolRunning = false;
			for (DEM_UINT i = 0; i < particlePools.size(); ++i)
			{
				ParticlePool *pool = particlePools.at(i);
				if (pool->running.load(memory_order::memory_order_acquire))
				{
					somePoolRunning = true;
					break;
				}
			}
			if (!somePoolRunning)
			{
				for (DEM_UINT i = 0; i < particlePools.size(); ++i)
				{
					(*particlePools.at(i))();
				}
			}
		}

		std::string str() const
		{
			std::strstream out;
			for (Particle *p : allParticles)
			{
				out << (*p) << endl;
			}
			out << '\0';
			return out.str();
		}

		DEM_UINT size() const
		{
			return particleCount;
		}

	private:
		vector<Particle*> allParticles;
		vector<ParticlePool*> particlePools;
		DEM_UINT maxThreads;
}; 

class Pipeline
{
	public:
		Pipeline()
		{
			m_id = sm_id;
			++sm_id;
			m_proc = new thread(&Pipeline::operator(), this);
			m_proc->join();
		}

		virtual void operator()(){};

		DEM_UINT getId() const { return m_id; }

	protected:
		static DEM_UINT		sm_id;
		DEM_UINT			m_id;
		thread*				m_proc;

		atomic<bool> terminated;
};

DEM_UINT Pipeline::sm_id = 0;

struct HelloPipeline : public Pipeline
{
	HelloPipeline()
	: Pipeline()
	{
	}

	void operator()()
	{
		for (DEM_UINT i = 0; i < 16; ++i)
		{ 
			printf("%d\n", m_id + i * i); 
		}
	}
};

int main(int argc, char** argv)
{
	DeusExMachina *app = DeusExMachina::Instance();

	HelloPipeline test;
	//for (;;)
	for (DEM_UINT i = 0; i < 16; ++i)
	{
		test();
	}
	
	DeusExMachina::Destroy();
	system("pause");
	return 0;
}