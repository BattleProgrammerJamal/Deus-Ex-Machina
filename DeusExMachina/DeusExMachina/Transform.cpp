#include "Transform.hpp"

using namespace DEM::Core;
using namespace DEM::Math;

Transform::Transform()
{
	m_position.set(0.0f, 0.0f, 0.0f);
	m_rotation.set(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale.set(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::Start()
{
	m_position.set(0.0f, 0.0f, 0.0f);
	m_rotation.set(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale.set(1.0f, 1.0f, 1.0f);
}

void Transform::Update(){}

Vector3 Transform::getPosition() const
{
	return m_position;
}

void Transform::setPosition(const Vector3& v)
{
	m_position = v;
}

Quaternion Transform::getRotation() const
{
	return m_rotation;
}

void Transform::setRotation(const Quaternion& v)
{
	m_rotation = v;
}

Vector3 Transform::getScale() const
{
	return m_scale;
}

void Transform::setScale(const Vector3& v)
{
	m_scale = v;
}

void Transform::Translate(const Vector3& v)
{
	m_position = m_position + v;
}

void Transform::Rotate(const Vector3& axis, float angle)
{
	Quaternion qRot(axis, angle);
	m_rotation = m_rotation * qRot * (-m_rotation);
}

void Transform::Scale(const Vector3& v)
{
	m_scale = m_scale * v;
}

Matrix<float> Transform::World() const
{
	Matrix<float> T = Matrix<float>::translation(m_position);
	Matrix<float> R = Matrix<float>::rotation(m_rotation);
	Matrix<float> S = Matrix<float>::scale(m_scale);
	return S * R * T;
}