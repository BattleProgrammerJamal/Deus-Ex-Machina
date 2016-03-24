#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>
#include <cstdint>

#define DEM_INT		std::int16_t
#define DEM_UINT	std::uint16_t

#define PTR_ALIGN_VALUE 16
#define AlignedPtr(ptr) (void*)(((uint32_t)ptr) + (PTR_ALIGN_VALUE - 1) & ~0xf)

#endif