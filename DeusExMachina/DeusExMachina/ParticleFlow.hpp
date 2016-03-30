#ifndef PARTICLE_FLOW_HPP
#define PARTICLE_FLOW_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <atomic>

#include "System.hpp"
#include "Math.hpp"

namespace DEM
{
	namespace Core
	{
		struct Particle
		{
			public:
				Math::Vector3 position;
				Math::Vector3 velocity;
				Math::Vector3 acceleration;
				Math::Vector3 force;
				Math::Vector3 oldPosition;
				float friction;
				float mass;
				DEM_UINT id;

				Particle(Math::Vector3 _position = Math::Vector3(0.0f, 0.0f, 0.0f), float _friction = 0.5f)
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

					oldPosition = Math::Vector3(position);
					force = force * friction;
				}

				void addForce(Math::Vector3 _force)
				{
					force += _force;
				}

				friend std::ostream& operator<<(std::ostream& out, const Particle& p);

			private:
				static float IG;
				static DEM_UINT sm_id;
		};

		struct ParticlePool
		{
			public:
				std::thread *poolThread;
				std::vector<Particle*> particles;
				System::Clock _clock;
				std::atomic<bool> running;

				ParticlePool(std::vector<Particle*> _particles)
				{
					particles = _particles;
					_clock.start();
					poolThread = new std::thread(_run, this);
					running.store(false, std::memory_order::memory_order_relaxed);
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
					if (poolThread->joinable() && !running.load(std::memory_order::memory_order_acquire))
					{
						running.store(true, std::memory_order::memory_order_relaxed);
						poolThread->join();
					}
				}

			private:
				static void _run(ParticlePool *pool)
				{
					for (Particle *p : pool->particles)
					{
						std::cout << "Update Particle<" << p->id << "> New Position : " << p->position << std::endl;
						p->update(pool->_clock.milliseconds());
					}
					pool->running.store(false, std::memory_order::memory_order_relaxed);
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
							Particle *p = new Particle(Math::Vector3(
								cos((float)(rand() % 15)) * 20,
								sin((float)(rand() % 15)) * 20,
								cos((float)(rand() % 10)) * 20
							));
							p->addForce(Math::Vector3(
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
				std::vector<Particle*> allParticles;
				std::vector<ParticlePool*> particlePools;
				DEM_UINT maxThreads;
		};
	};
};

#endif