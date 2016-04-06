#include "Color.hpp"

using namespace DEM::Math;

Color::Color()
{
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->a = 0.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(const Color& v)
{
	this->r = v.r;
	this->g = v.g;
	this->b = v.b;
	this->a = v.a;
}

Color::~Color()
{
}

void Color::set(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

float Color::length() const
{
	return sqrt(r * r + g * g + b * b + a * a);
}

float Color::distance(const Color& v) const
{
	return v.length() - length();
}

Color& Color::normalize()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	r /= l;
	g /= l;
	b /= l;
	a /= l;
	return *this;
}

Color Color::normalized()
{
	float l = length();
	l = (l == 0.0f) ? 1.0f : l;
	return Color(r / l, g / l, b / l, a / l);
}

float Color::dot(const Color& v)
{
	return (r * r) + (g * g) + (b * b) + (a * a);
}

Color Color::cross(const Color& v) const
{
	return Color(
		(g * v.b) - (b * v.g),
		(b * v.r) - (r * v.b),
		(a * v.g) - (g * v.a),
		(r * v.b) - (b * v.r)
	);
}

std::ostream& ::operator<<(std::ostream& out, const Color& v)
{
	out << "(r=" << v.r << "; g=" << v.g << "; b=" << v.b << "; a=" << v.a << ")";
	return out;
}

Color& Color::operator+=(const Color& v)
{
	r += v.r;
	g += v.g;
	b += v.b;
	return *this;
}

Color Color::operator+(const Color& v)
{
	Color u(*this);
	u.operator+=(v);
	return u;
}

Color& Color::operator-=(const Color& v)
{
	r -= v.r;
	g -= v.g;
	b -= v.b;
	return *this;
}

Color Color::operator-(const Color& v)
{
	Color u(*this);
	u.operator-=(v);
	return u;
}

Color& Color::operator*=(const Color& v)
{
	r *= v.r;
	g *= v.g;
	b *= v.b;
	return *this;
}

Color Color::operator*(const Color& v)
{
	Color u(*this);
	u.operator*=(v);
	return u;
}

Color& Color::operator/=(const Color& v)
{
	r /= (v.r == 0.0f) ? 1.0f : v.r;
	g /= (v.g == 0.0f) ? 1.0f : v.g;
	b /= (v.b == 0.0f) ? 1.0f : v.b;
	return *this;
}

Color Color::operator/(const Color& v)
{
	Color u(*this);
	u.operator/=(v);
	return u;
}

Color Color::operator-()
{
	return Color(-r, -g, -b, -a);
}

bool Color::operator==(const Color& v)
{
	return (r == v.r) && (g == v.g) && (b == v.b) && (a == v.a);
}

bool Color::operator<(const Color& v)
{
	return length() < v.length();
}

bool Color::operator!=(const Color& v)
{
	return !operator==(v);
}

bool Color::operator>(const Color& v)
{
	return !operator<(v) && !operator==(v);
}

bool Color::operator>=(const Color& v)
{
	return operator>(v) || operator==(v);
}

bool Color::operator<=(const Color& v)
{
	return operator<(v) || operator==(v);
}

Color& Color::operator+=(float v)
{
	r += v;
	g += v;
	b += v;
	return *this;
}

Color Color::operator+(float v)
{
	Color u(*this);
	u.operator+=(v);
	return u;
}

Color& Color::operator-=(float v)
{
	r -= v;
	g -= v;
	b -= v;
	return *this;
}

Color Color::operator-(float v)
{
	Color u(*this);
	u.operator-=(v);
	return u;
}

Color& Color::operator*=(float v)
{
	r *= v;
	g *= v;
	b *= v;
	return *this;
}

Color Color::operator*(float v)
{
	Color u(*this);
	u.operator*=(v);
	return u;
}

Color& Color::operator/=(float v)
{
	v = (v == 0.0f) ? 1.0f : v;
	r /= v;
	g /= v;
	b /= v;
	return *this;
}

Color Color::operator/(float v)
{
	Color u(*this);
	u.operator/=(v);
	return u;
}