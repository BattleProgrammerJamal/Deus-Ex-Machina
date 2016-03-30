#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include "Types.hpp"

namespace DEM
{
	namespace Core
	{
		class Actor;

		class Component
		{
			public:
				Component();
				virtual ~Component();

				virtual void Start()
				{
				}
				virtual void Update()
				{
				}

				Actor* getParent() const;
				void setParent(Actor* actor);

			protected:
				Actor*				m_parent;
				static DEM_UINT		sm_id;
				DEM_UINT			m_id;
		};
	};
};

#endif