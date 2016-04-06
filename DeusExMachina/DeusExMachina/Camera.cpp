#include "Camera.hpp"

using namespace DEM::Core;
using namespace DEM::Math;

Camera::Camera()
{
	m_view = Matrix<float>(4, 4);
	m_proj = Matrix<float>(4, 4);
}

Camera::~Camera()
{
}

void Camera::update()
{
}

Matrix<float> Camera::getView() const
{
	return m_view;
}

Matrix<float> Camera::getProj() const
{
	return m_proj;
}

OrthographicCamera::OrthographicCamera(const Vector2& position, float width, float height)
	: Camera()
{
	m_position = position;
	m_width = width;
	m_height = height;
	update();
}

OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::update()
{
	m_proj = Matrix<float>::projOrtho(
		(DEM_UINT)m_position.x,
		(DEM_UINT)(m_position.x + m_width),
		(DEM_UINT)m_position.y,
		(DEM_UINT)(m_position.y + m_height),
	0.0f, 1.0f);
}

Vector2 OrthographicCamera::getPosition() const
{
	return m_position;
}

void OrthographicCamera::setPosition(const Vector2& position)
{
	m_position = position;
}

float OrthographicCamera::getWidth() const
{
	return m_width;
}

void OrthographicCamera::setWidth(float width)
{
	m_width = width;
}

float OrthographicCamera::getHeight() const
{
	return m_height;
}

void OrthographicCamera::setHeight(float height)
{
	m_height = height;
}

void OrthographicCamera::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float cnear, float cfar)
	: Camera()
{
	m_fov = fov;
	m_aspect = aspect;
	m_near = cnear;
	m_far = cfar;

	eye.set(0.0f, 0.0f, 0.0f);
	target.set(0.0f, 0.0f, 0.0f);
	up.set(0.0f, 1.0f, 0.0f);

	updateProj();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::updateView()
{
	m_view = Matrix<float>::view(eye, target, up);
}

void PerspectiveCamera::updateProj()
{
	m_proj = Matrix<float>::projPersp(m_fov, m_aspect, m_near, m_far);
}

void PerspectiveCamera::update()
{
	updateView();
}

float PerspectiveCamera::getFOV() const
{
	return m_fov;
}

void PerspectiveCamera::setFOV(float fov)
{
	m_fov = fov;
}

float PerspectiveCamera::getAspect() const
{
	return m_aspect;
}

void PerspectiveCamera::setAspect(float aspect)
{
	m_aspect = aspect;
}

float PerspectiveCamera::getNear() const
{
	return m_near;
}

void PerspectiveCamera::setNear(float cnear)
{
	m_near = cnear;
}

float PerspectiveCamera::getFar() const
{
	return m_far;
}

void PerspectiveCamera::setFar(float cfar)
{
	m_far = cfar;
}