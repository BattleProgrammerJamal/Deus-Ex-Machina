#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <cmath>

namespace DEM
{
	namespace Math
	{
		class Vector2
		{
			public:
				float x, y;

				Vector2();
				Vector2(float x, float y);
				Vector2(const Vector2& v);

				virtual ~Vector2();

				void set(float x, float y);

				float length() const;

				float distance(const Vector2& v) const;

				Vector2& normalize();
				Vector2 normalized();

				float dot(const Vector2& v);

				Vector2 cross(const Vector2& v);

				friend std::ostream& operator<<(std::ostream& out, const Vector2& v);

				Vector2& operator+=(const Vector2& v);
				Vector2 operator+(const Vector2& v);

				Vector2& operator-=(const Vector2& v);
				Vector2 operator-(const Vector2& v);

				Vector2& operator*=(const Vector2& v);
				Vector2 operator*(const Vector2& v);

				Vector2& operator/=(const Vector2& v);
				Vector2 operator/(const Vector2& v);

				Vector2 operator-();

				bool operator==(const Vector2& v);
				bool operator<(const Vector2& v);
				bool operator!=(const Vector2& v);
				bool operator>(const Vector2& v);
				bool operator>=(const Vector2& v);
				bool operator<=(const Vector2& v);

				Vector2& operator+=(float v);
				Vector2 operator+(float v);

				Vector2& operator-=(float v);
				Vector2 operator-(float v);

				Vector2& operator*=(float v);
				Vector2 operator*(float v);

				Vector2& operator/=(float v);
				Vector2 operator/(float v);
		};
	};
};

#endif