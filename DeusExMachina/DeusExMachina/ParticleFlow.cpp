#include "ParticleFlow.hpp"

using namespace DEM::Core;

float Particle::IG = 1.0f / -9.81f;
DEM_UINT Particle::sm_id = 0;

std::ostream& ::operator<<(std::ostream& out, const Particle& p)
{
	out << "Particle <" << p.id << "> :" << std::endl << "\tposition = " << p.position << std::endl <<
		"\tvelocity = " << p.velocity << std::endl <<
		"\tacceleration = " << p.acceleration << std::endl <<
		"\tforce = " << p.force << std::endl <<
		"\tfriction = " << p.friction << std::endl <<
		"\tmass = " << p.mass << std::endl <<
		"\toldPosition = " << p.oldPosition << std::endl <<
		std::endl;
	return out;
}

