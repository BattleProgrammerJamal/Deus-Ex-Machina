#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Types.hpp"

#define ROT32(x, y) ((x << y) | (x >> (32 - y)))

namespace DEM
{
	namespace System
	{
		class Crypto
		{
			public:
				/**
				static DEM_UINT Hash32(std::string key){ return Murmur32(key, 32); }

				static DEM_UINT Murmur32(std::string key, DEM_UINT seed)
				{
					static const DEM_UINT c1 = 0xcc9e2d51;
					static const DEM_UINT c2 = 0x1b873593;
					static const DEM_UINT r1 = 15;
					static const DEM_UINT r2 = 13;
					static const DEM_UINT m = 5;
					static const DEM_UINT n = 0xe6546b64;
					DEM_UINT len = key.size();
					DEM_UINT hash = seed;

					const int nblocks = len / 4;
					const DEM_UINT *blocks = (const DEM_UINT *)key.c_str();
					int i;
					DEM_UINT k;
					for (i = 0; i < nblocks; i++) 
					{
						k = blocks[i];
						k *= c1;
						k = ROT32(k, r1);
						k *= c2;

						hash ^= k;
						hash = ROT32(hash, r2) * m + n;
					}

					const DEM_UINT *tail = (const DEM_UINT *)(key.c_str() + nblocks * 4);
					DEM_UINT k1 = 0;

					switch (len & 3) 
					{
						case 3:
							k1 ^= tail[2] << 16;
						case 2:
							k1 ^= tail[1] << 8;
						case 1:
							k1 ^= tail[0];

							k1 *= c1;
							k1 = ROT32(k1, r1);
							k1 *= c2;
							hash ^= k1;
					}

					hash ^= len;
					hash ^= (hash >> 16);
					hash *= 0x85ebca6b;
					hash ^= (hash >> 13);
					hash *= 0xc2b2ae35;
					hash ^= (hash >> 16);

					return hash;
				}
				*/
		};
	};
};

#endif