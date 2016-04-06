#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <cmath>

namespace DEM
{
	namespace Math
	{
		class Color
		{
			public:
				float r, g, b, a;

				Color();
				Color(float r, float g, float b, float a);
				Color(const Color& v);

				virtual ~Color();

				void set(float r, float g, float b, float a);

				float length() const;

				float distance(const Color& v) const;

				Color& normalize();
				Color normalized();

				float dot(const Color& v);

				Color cross(const Color& v) const;

				friend std::ostream& operator<<(std::ostream& out, const Color& v);

				Color& operator+=(const Color& v);
				Color operator+(const Color& v);

				Color& operator-=(const Color& v);
				Color operator-(const Color& v);

				Color& operator*=(const Color& v);
				Color operator*(const Color& v);

				Color& operator/=(const Color& v);
				Color operator/(const Color& v);

				Color operator-();

				bool operator==(const Color& v);
				bool operator<(const Color& v);
				bool operator!=(const Color& v);
				bool operator>(const Color& v);
				bool operator>=(const Color& v);
				bool operator<=(const Color& v);

				Color& operator+=(float v);
				Color operator+(float v);

				Color& operator-=(float v);
				Color operator-(float v);

				Color& operator*=(float v);
				Color operator*(float v);

				Color& operator/=(float v);
				Color operator/(float v);
		};
	};
};

#endif