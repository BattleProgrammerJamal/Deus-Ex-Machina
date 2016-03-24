#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include "Types.hpp"

namespace DEM
{
	namespace Core
	{
		class Component
		{
			public:
				Component();
				virtual ~Component();

				virtual void Start(){}
				virtual void Update(){}

			protected:
				static DEM_UINT sm_id;
				DEM_UINT m_id;
		};
	};
};

#endif