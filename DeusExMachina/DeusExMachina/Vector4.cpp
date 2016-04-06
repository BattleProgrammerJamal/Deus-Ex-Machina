#include "Vector4.hpp"

using namespace DEM::Math;

Vector4::Vector4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(const Vector4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

Vector4::~Vector4()
{
}

void Vector4::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::distance(const Vector4& v) const
{
	return v.length() - length();
}

Vector4& Vector4::normalize()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	x /= l;
	y /= l;
	z /= l;
	w /= l;
	return *this;
}

Vector4 Vector4::normalized()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	return Vector4(x / l, y / l, z / l, w / l);
}

float Vector4::dot(const Vector4& v)
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

Vector4 Vector4::cross(const Vector4& v) const
{
	return Vector4(
		(y * v.z) - (z * v.y),
		(z * v.w) - (w * v.z),
		(w * v.x) - (x * v.w),
		(x * v.y) - (y * v.x)
	);
}

std::ostream& ::operator<<(std::ostream& out, const Vector4& v)
{
	out << "(x=" << v.x << "; y=" << v.y << "; z=" << v.z << "; w=" << v.w << ")";
	return out;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4 Vector4::operator+(const Vector4& v)
{
	Vector4 u(*this);
	u.operator+=(v);
	return u;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& v)
{
	Vector4 u(*this);
	u.operator-=(v);
	return u;
}

Vector4& Vector4::operator*=(const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

Vector4 Vector4::operator*(const Vector4& v)
{
	Vector4 u(*this);
	u.operator*=(v);
	return u;
}

Vector4& Vector4::operator/=(const Vector4& v)
{
	x /= (v.x == 0.0f) ? 1.0f : v.x;
	y /= (v.y == 0.0f) ? 1.0f : v.y;
	z /= (v.z == 0.0f) ? 1.0f : v.z;
	w /= (v.w == 0.0f) ? 1.0f : v.w;
	return *this;
}

Vector4 Vector4::operator/(const Vector4& v)
{
	Vector4 u(*this);
	u.operator/=(v);
	return u;
}

Vector4 Vector4::operator-()
{
	return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator==(const Vector4& v)
{
	return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}

bool Vector4::operator<(const Vector4& v)
{
	return length() < v.length();
}

bool Vector4::operator!=(const Vector4& v)
{
	return !operator==(v);
}

bool Vector4::operator>(const Vector4& v)
{
	return !operator<(v) && !operator==(v);
}

bool Vector4::operator>=(const Vector4& v)
{
	return operator>(v) || operator==(v);
}

bool Vector4::operator<=(const Vector4& v)
{
	return operator<(v) || operator==(v);
}

Vector4& Vector4::operator+=(float v)
{
	x += v;
	y += v;
	z += v;
	w += v;
	return *this;
}

Vector4 Vector4::operator+(float v)
{
	Vector4 u(*this);
	u.operator+=(v);
	return u;
}

Vector4& Vector4::operator-=(float v)
{
	x -= v;
	y -= v;
	z -= v;
	w -= v;
	return *this;
}

Vector4 Vector4::operator-(float v)
{
	Vector4 u(*this);
	u.operator-=(v);
	return u;
}

Vector4& Vector4::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;
	return *this;
}

Vector4 Vector4::operator*(float v)
{
	Vector4 u(*this);
	u.operator*=(v);
	return u;
}

Vector4& Vector4::operator/=(float v)
{
	v = (v == 0.0f) ? 1.0f : v;
	x /= v;
	y /= v;
	z /= v;
	w /= v;
	return *this;
}

Vector4 Vector4::operator/(float v)
{
	Vector4 u(*this);
	u.operator/=(v);
	return u;
}