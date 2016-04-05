#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <iostream>

#include "Types.hpp"

namespace DEM
{
	namespace Core
	{
		class Resource
		{
			public:
				Resource();
				virtual ~Resource();

				virtual Resource& load();

			protected:
				static DEM_UINT		sm_id;
				DEM_UINT			m_id;

		};
	};
};

#endif