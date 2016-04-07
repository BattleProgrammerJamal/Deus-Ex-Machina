#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <iostream>
#include <string>

#include "Component.hpp"
#include "Math.hpp"

namespace DEM
{
	namespace Core
	{
		class Transform : public Component
		{
			public:
				Transform();
				virtual ~Transform();

				void Start();
				void Update();

				Math::Vector3 getPosition() const;
				void setPosition(const Math::Vector3& v);

				Math::Quaternion getRotation() const;
				void setRotation(const Math::Quaternion& v);

				Math::Vector3 getScale() const;
				void setScale(const Math::Vector3& v);

				void Translate(const Math::Vector3& v);
				void Rotate(const Math::Vector3& axis, float angle);
				void Scale(const Math::Vector3& v);

				Math::Matrix<float> World() const;

			protected:
				Math::Vector3		m_position;
				Math::Quaternion	m_rotation;
				Math::Vector3		m_scale;
		};
	};
};

#endif