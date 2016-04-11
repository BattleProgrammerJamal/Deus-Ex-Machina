#ifndef MORPH_TARGET_GEOMETRY_HPP
#define MORPH_TARGET_GEOMETRY_HPP

#include <iostream>
#include <vector>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Math.hpp"
#include "Geometry.hpp"

namespace DEM
{
	namespace Core
	{
		struct MorphTarget
		{
			Geometry*	geometry;
			float		weight;

			MorphTarget(Geometry *_geometry, float _weight)
			{
				geometry = _geometry;
				weight = _weight;
			}
		};

		class MorphTargetGeometry : public Geometry
		{
			public:
				MorphTargetGeometry(Geometry *base = 0, std::vector<MorphTarget*> morphTargets = std::vector<MorphTarget*>());

				void load();

				MorphTargetGeometry& addMorphTarget(MorphTarget *morphTarget);

				std::vector<MorphTarget*> getMorphTargets() const;

			protected:
				Geometry*					m_baseGeometry;
				std::vector<MorphTarget*>	m_morphTargets;
		};
	};
};

#endif