#include "Vector2.hpp"

using namespace DEM::Math;

Vector2::Vector2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
}

Vector2::~Vector2()
{
}

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::distance(const Vector2& v) const
{
	return v.length() - length();
}

Vector2& Vector2::normalize()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	x /= l;
	y /= l;
	return *this;
}

Vector2 Vector2::normalized()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	return Vector2(x / l, y / l);
}

float Vector2::dot(const Vector2& v)
{
	return (x * x) + (y * y);
}

Vector2 Vector2::cross(const Vector2& v)
{
	return Vector2(y * v.x - v.y * x, x * v.y - v.x * y);
}

std::ostream& ::operator<<(std::ostream& out, const Vector2& v)
{
	out << "(x=" << v.x << "; y=" << v.y << ")";
	return out;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 u(*this);
	u.operator+=(v);
	return u;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 u(*this);
	u.operator-=(v);
	return u;
}

Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& v)
{
	Vector2 u(*this);
	u.operator*=(v);
	return u;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
	x /= (v.x == 0.0f) ? 1.0f : v.x;
	y /= (v.y == 0.0f) ? 1.0f : v.y;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& v)
{
	Vector2 u(*this);
	u.operator/=(v);
	return u;
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& v)
{
	return (x == v.x) && (y == v.y);
}

bool Vector2::operator<(const Vector2& v)
{
	return length() < v.length();
}

bool Vector2::operator!=(const Vector2& v)
{
	return !operator==(v);
}

bool Vector2::operator>(const Vector2& v)
{
	return !operator<(v) && !operator==(v);
}

bool Vector2::operator>=(const Vector2& v)
{
	return operator>(v) || operator==(v);
}

bool Vector2::operator<=(const Vector2& v)
{
	return operator<(v) || operator==(v);
}

Vector2& Vector2::operator+=(float v)
{
	x += v;
	y += v;
	return *this;
}

Vector2 Vector2::operator+(float v)
{
	Vector2 u(*this);
	u.operator+=(v);
	return u;
}

Vector2& Vector2::operator-=(float v)
{
	x -= v;
	y -= v;
	return *this;
}

Vector2 Vector2::operator-(float v)
{
	Vector2 u(*this);
	u.operator-=(v);
	return u;
}

Vector2& Vector2::operator*=(float v)
{
	x *= v;
	y *= v;
	return *this;
}

Vector2 Vector2::operator*(float v)
{
	Vector2 u(*this);
	u.operator*=(v);
	return u;
}

Vector2& Vector2::operator/=(float v)
{
	v = (v == 0.0f) ? 1.0f : v;
	x /= v;
	y /= v;
	return *this;
}

Vector2 Vector2::operator/(float v)
{
	Vector2 u(*this);
	u.operator/=(v);
	return u;
}