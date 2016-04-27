#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <strstream>
#include <sstream>
#include <array>
#include <vector>

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Asset.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Math.hpp"

#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#define DEM_MAXIMUM_TEXTURES 16

namespace DEM
{
	namespace Core
	{
		struct ShaderUValue
		{
			public:
				ShaderUValue()
				{
				}

				virtual ~ShaderUValue()
				{
				}

			protected:
		};
		struct ShaderUInt : public ShaderUValue 
		{
			public:
				ShaderUInt(DEM_INT *data)
					: ShaderUValue()
				{
					_data = data;
				}

				DEM_INT get()
				{
					return *((DEM_INT*)_data);
				}

				void set(DEM_INT *data)
				{
					_data = data;
				}

			private:
				DEM_INT* _data;
		};
		struct ShaderUFloat : public ShaderUValue 
		{
			public:
				ShaderUFloat(float *data)
					: ShaderUValue()
				{
					_data = data;
				}

				float get()
				{
					return *((float*)_data);
				}

				void set(float *data)
				{
					_data = data;
				}

			private:
				float* _data;
		};
		struct ShaderUFloat2 : public ShaderUValue 
		{
			public:
				ShaderUFloat2(Math::Vector2 *data)
					: ShaderUValue()
				{
					_data = data;
				}

				Math::Vector2 get()
				{
					return *((Math::Vector2*)_data);
				}

				void set(Math::Vector2 *data)
				{
					_data = data;
				}

			private:
				Math::Vector2* _data;
		};
		struct ShaderUFloat3 : public ShaderUValue 
		{
			public:
				ShaderUFloat3(Math::Vector3 *data)
					: ShaderUValue()
				{
					_data = data;
				}

				Math::Vector3 get()
				{
					return *((Math::Vector3*)_data);
				}

				void set(Math::Vector3 *data)
				{
					_data = data;
				}

			private:
				Math::Vector3* _data;
		};
		struct ShaderUQuaternion : public ShaderUValue 
		{
			public:
				ShaderUQuaternion(Math::Quaternion *data)
					: ShaderUValue()
				{
					_data = data;
				}

				Math::Quaternion get()
				{
					return *((Math::Quaternion*)_data);
				}

				void set(Math::Quaternion *data)
				{
					_data = data;
				}

			private:
				Math::Quaternion* _data;
		};
		struct ShaderUMat3 : public ShaderUValue 
		{
			public:
				ShaderUMat3(glm::mat3& data)
					: ShaderUValue()
				{
					_data = data;
				}

				glm::mat3 get()
				{
					return _data;
				}

				void set(glm::mat3& data)
				{
					_data = data;
				}

			private:
				glm::mat3		_data;
		};
		struct ShaderUMat4 : public ShaderUValue 
		{
			public:
				ShaderUMat4(glm::mat4& data)
					: ShaderUValue()
				{
					_data = data;
				}

				glm::mat4 get()
				{
					return _data;
				}

				void set(glm::mat4& data)
				{
					_data = data;
				}

			private:
				glm::mat4		_data;
		};

		struct ShaderUniform
		{
			std::string			name;
			ShaderUValue*		value;

			ShaderUniform(std::string _name, ShaderUValue *_value)
			{
				name = _name;
				value = _value;
			}

			virtual ~ShaderUniform()
			{
				delete value;
			}
		};

		class Material : public Asset
		{
			public:
				std::vector<ShaderUniform*> uniforms;
				Math::Color baseColor;

				Material();
				Material(std::string vs, std::string fs);
				Material(const Material& material);
				virtual ~Material();

				void bind();
				void unbind();

				virtual void updateParameters();

				Shader* getShaderProgram() const;
				void setShaderProgram(Shader *shader);

				Material& loadTexture(const std::string path);

				Texture* operator[](DEM_UINT index);

			protected:
				std::array<Texture*, DEM_MAXIMUM_TEXTURES>		m_textures;
				Shader*											m_shaderProgram;
		};
	};
};

#endif