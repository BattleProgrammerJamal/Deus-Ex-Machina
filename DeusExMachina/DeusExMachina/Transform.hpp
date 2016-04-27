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
				Math::Vector3		position;
				Math::Quaternion	rotation;
				Math::Vector3		scale;

				Transform();
				virtual ~Transform();

				void Start();
				void Update();

				void Translate(const Math::Vector3& v);
				void Rotate(const Math::Vector3& axis, float angle);
				void Scale(const Math::Vector3& v);

				virtual Math::Matrix<float> World() const;

			protected:
		};
	};
};

#endif