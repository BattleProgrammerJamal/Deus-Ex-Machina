#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <cmath>

namespace DEM
{
	namespace Math
	{
		class Vector3
		{
			public:
				float x, y, z;

				Vector3();
				Vector3(float x, float y, float z);
				Vector3(const Vector3& v);

				virtual ~Vector3();

				float length() const;

				float distance(const Vector3& v) const;

				Vector3& normalize();
				Vector3 normalized();

				float dot(const Vector3& v);

				Vector3 cross(const Vector3& v);

				friend std::ostream& operator<<(std::ostream& out, const Vector3& v);

				Vector3& operator+=(const Vector3& v);
				Vector3 operator+(const Vector3& v);

				Vector3& operator-=(const Vector3& v);
				Vector3 operator-(const Vector3& v);

				Vector3& operator*=(const Vector3& v);
				Vector3 operator*(const Vector3& v);

				Vector3& operator/=(const Vector3& v);
				Vector3 operator/(const Vector3& v);

				Vector3 operator-();

				bool operator==(const Vector3& v);
				bool operator<(const Vector3& v);
				bool operator!=(const Vector3& v);
				bool operator>(const Vector3& v);
				bool operator>=(const Vector3& v);
				bool operator<=(const Vector3& v);

				Vector3& operator+=(float v);
				Vector3 operator+(float v);

				Vector3& operator-=(float v);
				Vector3 operator-(float v);

				Vector3& operator*=(float v);
				Vector3 operator*(float v);

				Vector3& operator/=(float v);
				Vector3 operator/(float v);
		};
	};
};

#endif