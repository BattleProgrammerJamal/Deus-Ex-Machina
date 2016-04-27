#include "Transform.hpp"

using namespace DEM::Core;
using namespace DEM::Math;

Transform::Transform()
{
	position.set(0.0f, 0.0f, 0.0f);
	rotation.set(0.0f, 0.0f, 0.0f, 1.0f);
	scale.set(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::Start()
{
	position.set(0.0f, 0.0f, 0.0f);
	rotation.set(0.0f, 0.0f, 0.0f, 1.0f);
	scale.set(1.0f, 1.0f, 1.0f);
}

void Transform::Update(){}

void Transform::Translate(const Vector3& v)
{
	position = position + v;
}

void Transform::Rotate(const Vector3& axis, float angle)
{
	Quaternion qRot(axis, angle);
	rotation = qRot * rotation * (-qRot);
}

void Transform::Scale(const Vector3& v)
{
	scale = scale * v;
}

Matrix<float> Transform::World() const
{
	Matrix<float> T = Matrix<float>::translation(position);
	Matrix<float> R = Matrix<float>::rotation(rotation);
	Matrix<float> S = Matrix<float>::scale(scale);
	return S * R * T;
}