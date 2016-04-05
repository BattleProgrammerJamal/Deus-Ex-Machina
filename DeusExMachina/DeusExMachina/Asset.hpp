#ifndef ASSET_HPP
#define ASSET_HPP

#include <iostream>

#include "Types.hpp"

namespace DEM
{
	namespace Core
	{
		class Asset
		{
			public:
				Asset(const std::string& name);
				virtual ~Asset();

				std::string getName() const;
				void setName(const std::string& name);

			protected:
				static DEM_UINT		sm_id;
				DEM_UINT			m_id;
				std::string			m_name;
		};
	};
};

#endif