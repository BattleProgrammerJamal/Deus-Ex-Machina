#include "Vector3.hpp"

using namespace DEM::Math;

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::~Vector3()
{
}

void Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::distance(const Vector3& v) const
{
	return v.length() - length();
}

Vector3& Vector3::normalize()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	x /= l;
	y /= l;
	z /= l;
	return *this;
}

Vector3 Vector3::normalized()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	return Vector3(x / l, y / l, z / l);
}

float Vector3::dot(const Vector3& v)
{
	return (x * x) + (y * y) + (z * z);
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(
		(y * v.z) - (z * v.y),
		(z * v.x) - (x * v.z),
		(x * v.y) - (y * v.x)
		);
}

std::ostream& ::operator<<(std::ostream& out, const Vector3& v)
{
	out << "(x=" << v.x << "; y=" << v.y << "; z=" << v.z << ")";
	return out;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& v)
{
	Vector3 u(*this);
	u.operator+=(v);
	return u;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v)
{
	Vector3 u(*this);
	u.operator-=(v);
	return u;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& v)
{
	Vector3 u(*this);
	u.operator*=(v);
	return u;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	x /= (v.x == 0.0f) ? 1.0f : v.x;
	y /= (v.y == 0.0f) ? 1.0f : v.y;
	z /= v.z;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& v)
{
	Vector3 u(*this);
	u.operator/=(v);
	return u;
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3& v)
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

bool Vector3::operator<(const Vector3& v)
{
	return length() < v.length();
}

bool Vector3::operator!=(const Vector3& v)
{
	return !operator==(v);
}

bool Vector3::operator>(const Vector3& v)
{
	return !operator<(v) && !operator==(v);
}

bool Vector3::operator>=(const Vector3& v)
{
	return operator>(v) || operator==(v);
}

bool Vector3::operator<=(const Vector3& v)
{
	return operator<(v) || operator==(v);
}

Vector3& Vector3::operator+=(float v)
{
	x += v;
	y += v;
	z += v;
	return *this;
}

Vector3 Vector3::operator+(float v)
{
	Vector3 u(*this);
	u.operator+=(v);
	return u;
}

Vector3& Vector3::operator-=(float v)
{
	x -= v;
	y -= v;
	z -= v;
	return *this;
}

Vector3 Vector3::operator-(float v)
{
	Vector3 u(*this);
	u.operator-=(v);
	return u;
}

Vector3& Vector3::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

Vector3 Vector3::operator*(float v)
{
	Vector3 u(*this);
	u.operator*=(v);
	return u;
}

Vector3& Vector3::operator/=(float v)
{
	v = (v == 0.0f) ? 1.0f : v;
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

Vector3 Vector3::operator/(float v)
{
	Vector3 u(*this);
	u.operator/=(v);
	return u;
}