#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <iostream>
#include <cmath>

namespace DEM
{
	namespace Math
	{
		class Vector4
		{
			public:
				float x, y, z, w;

				Vector4();
				Vector4(float x, float y, float z, float w);
				Vector4(const Vector4& v);

				virtual ~Vector4();

				void set(float x, float y, float z, float w);

				float length() const;

				float distance(const Vector4& v) const;

				Vector4& normalize();
				Vector4 normalized();

				float dot(const Vector4& v);

				Vector4 cross(const Vector4& v) const;

				friend std::ostream& operator<<(std::ostream& out, const Vector4& v);

				Vector4& operator+=(const Vector4& v);
				Vector4 operator+(const Vector4& v);

				Vector4& operator-=(const Vector4& v);
				Vector4 operator-(const Vector4& v);

				Vector4& operator*=(const Vector4& v);
				Vector4 operator*(const Vector4& v);

				Vector4& operator/=(const Vector4& v);
				Vector4 operator/(const Vector4& v);

				Vector4 operator-();

				bool operator==(const Vector4& v);
				bool operator<(const Vector4& v);
				bool operator!=(const Vector4& v);
				bool operator>(const Vector4& v);
				bool operator>=(const Vector4& v);
				bool operator<=(const Vector4& v);

				Vector4& operator+=(float v);
				Vector4 operator+(float v);

				Vector4& operator-=(float v);
				Vector4 operator-(float v);

				Vector4& operator*=(float v);
				Vector4 operator*(float v);

				Vector4& operator/=(float v);
				Vector4 operator/(float v);
		};
	};
};

#endif