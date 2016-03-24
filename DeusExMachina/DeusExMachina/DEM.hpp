#ifndef DEM_HPP
#define DEM_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "System.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Actor.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace DEM
{
	static const char* name = "Deus Ex Machina";
	static DEM_UINT version_major = 1;
	static DEM_UINT version_minor = 0;

	class DeusExMachina
	{
		public:
			~DeusExMachina();

			static DeusExMachina* Instance();

			static void Destroy();

			System::System* getSystem() const;

		private:
			DeusExMachina();
			static DeusExMachina *sm_instance;

			System::System *m_system;
	};
};

#endif