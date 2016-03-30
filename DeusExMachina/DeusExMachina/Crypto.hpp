#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Types.hpp"

namespace DEM
{
	namespace System
	{
		class Crypto
		{
			public:
				static DEM_UINT Hash32(std::string key)
				{ 
					DEM_UINT rslt = 2;
					for (DEM_UINT index = 0; index < key.length(); ++index)
					{
						rslt = ROT32(rslt + static_cast<DEM_UINT>(key[index]), 4);
					}
					return rslt;
				}

			private:
				static DEM_UINT ROT32(DEM_UINT x, DEM_UINT y)
				{
					return (x << y) | (x >> (32 - y));
				}
		};
	};
};

#endif