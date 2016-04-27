#ifndef CONVOLUTION_MATERIAL_HPP
#define CONVOLUTION_MATERIAL_HPP

#include <iostream>
#include <vector>

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Math.hpp"
#include "Color.hpp"
#include "Material.hpp"

namespace DEM
{
	namespace Core
	{
		class ConvolutionMaterial : public Material
		{
			public:
				std::vector<glm::mat3> kernels;

				ConvolutionMaterial(std::vector<glm::mat3> _kernels = std::vector<glm::mat3>());
				~ConvolutionMaterial();

				void updateParameters();

				ConvolutionMaterial& operator<<(glm::mat3 kernel)
				{
					kernels.emplace_back(kernel);
					return *this;
				}

			private:
		};
	};
};

#endif