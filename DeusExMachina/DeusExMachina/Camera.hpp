#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include "Math.hpp"

namespace DEM
{
	namespace Core
	{
		class Camera
		{
			public:
				Camera();
				virtual ~Camera();

				virtual void update();

				Math::Matrix<float>* getView() const;

				Math::Matrix<float>* getProj() const;

			protected:
				Math::Matrix<float> *m_view;
				Math::Matrix<float> *m_proj;
		};

		class OrthographicCamera : public Camera
		{
			public:
				OrthographicCamera(const Math::Vector2& position, float width, float height);
				~OrthographicCamera();

				void update();

				Math::Vector2 getPosition() const;
				void setPosition(const Math::Vector2& position);

				float getWidth() const;
				void setWidth(float width);

				float getHeight() const;
				void setHeight(float height);

				void setSize(float width, float height);

			private:
				Math::Vector2	m_position;
				float			m_width;
				float			m_height;
		};

		class PerspectiveCamera : public Camera
		{
			public:
				Math::Vector3		eye;
				Math::Vector3		target;
				Math::Vector3		up;

				PerspectiveCamera(float fov, float aspect, float cnear, float cfar);
				~PerspectiveCamera();

				void updateView();
				void updateProj();
				void update();

				float getFOV() const;
				void setFOV(float fov);

				float getAspect() const;
				void setAspect(float aspect);

				float getNear() const;
				void setNear(float cnear);

				float getFar() const;
				void setFar(float cfar);

			private:
				float				m_fov;
				float				m_aspect;
				float				m_near;
				float				m_far;
		};
	};
};

#endif