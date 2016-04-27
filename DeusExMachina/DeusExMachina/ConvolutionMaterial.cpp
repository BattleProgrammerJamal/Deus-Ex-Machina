#include "ConvolutionMaterial.hpp"

using namespace DEM;
using namespace DEM::Core;

ConvolutionMaterial::ConvolutionMaterial(std::vector<glm::mat3> _kernels)
	: Material("Assets/shaders/convolution.vs", "Assets/shaders/convolution.fs") 
{
	kernels = _kernels;
}

ConvolutionMaterial::~ConvolutionMaterial()
{
}

void ConvolutionMaterial::updateParameters()
{
	GLuint shaderID = m_shaderProgram->getProgram();

	DEM_UINT index = 0;
	for (glm::mat3 kernel : kernels)
	{
		std::strstream streamData, streamActive;
		streamActive << "u_kernels[" << index << "].active" << '\0';
		streamData << "u_kernels[" << index  << "].data" << '\0';

		GLuint kernelActiveLocation = glGetUniformLocation(shaderID, streamActive.str());
		glUniform1i(kernelActiveLocation, 1);
		GLuint kernelLocation = glGetUniformLocation(shaderID, streamData.str());
		glUniformMatrix3fv(kernelLocation, 1, GL_FALSE, glm::value_ptr(kernel));
		++index;
	}
}