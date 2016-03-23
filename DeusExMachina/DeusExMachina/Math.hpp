#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <cmath>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

#define PI 3.1459f

namespace DEM
{
	namespace Math
	{
		template <typename T>
		T rad(T angle)
		{
			return angle * PI / 180;
		}

		template <typename T>
		T deg(T angle)
		{
			return angle * 180 / PI;
		}

		template <typename T>
		T lerp(T a, T b, float t)
		{
			return a * (1.0f - t) + (b * t);
		}
	};
};

#endif