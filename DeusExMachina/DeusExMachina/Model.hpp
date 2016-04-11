#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include "Math.hpp"
#include "Color.hpp"
#include "Resource.hpp"
#include "Geometry.hpp"
#include "Material.hpp"
#include "LambertMaterial.hpp"

#include "tiny_obj_loader.h"

namespace DEM
{
	namespace Core
	{
		class Mesh;

		class Model : public Resource 
		{
			public:
				Model(const std::string& path);
				~Model();

				Model& load();

				Mesh* Instanciate(DEM_UINT index);
				Mesh* InstanciateAll();

				std::string getPath() const;
				void setPath(const std::string& path);

			protected:
				std::vector<tinyobj::shape_t>			m_shapes;
				std::vector<tinyobj::material_t>		m_materials;
				std::string								m_path;
		};
	};
};

#endif