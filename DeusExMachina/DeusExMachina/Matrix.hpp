#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cmath>
#include <strstream>

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Types.hpp"

namespace DEM
{
	namespace Math
	{
		template <typename T>
		class Matrix
		{
			public:
				Matrix()
				{
					m_l = 4;
					m_c = 4;
					m_data = new T[m_l * m_c];
					identity();
				}

				Matrix(DEM_UINT L, DEM_UINT C)
				{
					m_l = L;
					m_c = C;
					m_data = new T[m_l * m_c];
					identity();
				}

				Matrix(const Matrix<T>& m)
				{
					m_l = m.getL();
					m_c = m.getC();
					m_data = new T[m_l * m_c];

					for (DEM_UINT i = 0; i < m_l * m_c; ++i)
					{
						m_data[i] = m.getData(i);
					}
				}

				virtual ~Matrix()
				{
					delete[] m_data;
				}

				std::string str()
				{
					std::strstream out;
					for (DEM_UINT i = 0; i < m_l; ++i)
					{
						for (DEM_UINT j = 0; j < m_c; ++j)
						{
							DEM_UINT id = index(i, j);
							out << m_data[id] << "\t";
						}
						out << std::endl;
					}
					out << '\0';
					return out.str();
				}

				DEM_UINT index(DEM_UINT i, DEM_UINT j)
				{
					return i + j * m_l;
				}

				void zero()
				{
					for (DEM_UINT i = 0; i < m_l * m_c; ++i)
					{
						m_data[i] = 0;
					}
				}

				DEM_UINT size() const
				{
					return m_l * m_c;
				}

				void identity()
				{
					for (DEM_UINT i = 0; i < m_l; ++i)
					{
						for (DEM_UINT j = 0; j < m_c; ++j)
						{
							DEM_UINT id = index(i, j);
							if (i == j)
							{
								m_data[id] = 1.0f;
							}
							else
							{
								m_data[id] = 0.0f;
							}
						}
					}
				}

				T& getData(DEM_UINT index) const
				{
					return m_data[index];
				}

				void setData(DEM_UINT index, T value)
				{
					m_data[index] = value;
				}

				Matrix<T> operator+(const Matrix<T>& m)
				{
					Matrix<T> mat(*this);
					mat.operator+=(m);
					return mat;
				}

				Matrix<T>& operator+=(const Matrix<T>& m)
				{
					for (DEM_UINT i = 0; i < m_l * m_c; ++i)
					{
						setData(i, m_data[i] + m.getData(i));
					}
					return *this;
				}

				Matrix<T> operator-(const Matrix<T>& m)
				{
					Matrix<T> mat(*this);
					mat.operator-=(m);
					return mat;
				}

				Matrix<T>& operator-=(const Matrix<T>& m)
				{
					for (DEM_UINT i = 0; i < m_l * m_c; ++i)
					{
						setData(i, m_data[i] - m.getData(i));
					}
					return *this;
				}

				Matrix<T> operator*(const Matrix<T>& m)
				{
					Matrix<T> mat(*this);
					mat.operator*=(m);
					return mat;
				}

				Matrix<T>& operator*=(const Matrix<T>& m)
				{
					for (DEM_UINT i = 0; i < m_l; ++i)
					{
						for (DEM_UINT j = 0; j < m_c; ++j)
						{
							T sum = T();

							for (DEM_UINT k = 0; k < m_c; ++k)
							{
								sum = sum + (m_data[index(i, j)] * m.getData(index(k, i)));
							}

							setData(i, sum);
						}
					}
					return *this;
				}

				Matrix<T> operator-()
				{
					Matrix<T> m(m_l, m_c);
					for (DEM_UINT i = 0; i < m.size(); ++i)
					{
						m.setData(i, -m_data[i]);
					}
					return m;
				}

				static Matrix<float> translation(const Vector3& v)
				{
					Matrix<float> T(4, 4);

					T.setData(T.index(0, 0), 1.0f);
					T.setData(T.index(1, 1), 1.0f);
					T.setData(T.index(2, 2), 1.0f);
					T.setData(T.index(3, 3), 1.0f);

					T.setData(T.index(0, 3), v.x);
					T.setData(T.index(1, 3), v.y);
					T.setData(T.index(2, 3), v.z);

					return T;
				}

				static Matrix<float> rotation(const Quaternion& q)
				{
					Matrix<float> T(4, 4);
					q.setRotationMatrix(T.ptr_value());
					return T;
				}

				static Matrix<float> scale(const Vector3& v)
				{
					Matrix<float> T(4, 4);

					T.setData(T.index(0, 0), v.x);
					T.setData(T.index(1, 1), v.y);
					T.setData(T.index(2, 2), v.z);
					T.setData(T.index(3, 3), 1.0f);

					return T;
				}

				static Matrix<float> projOrtho(DEM_UINT _left, DEM_UINT _right, DEM_UINT _top, DEM_UINT _down, float cnear, float cfar)
				{
					float left = _left, right = _right, top = _top, down = _down;

					Matrix<float> T(4, 4);

					T.setData(T.index(0, 0), 2.0f / (right - left));
					T.setData(T.index(0, 3), -(right + left) / (right - left));

					T.setData(T.index(1, 1), 2.0f / (top - down));
					T.setData(T.index(1, 3), -(top + down) / (top - down));

					T.setData(T.index(2, 2), -2.0f / (cfar - cnear));
					T.setData(T.index(2, 3), -(cfar + cnear) / (cfar - cnear));

					T.setData(T.index(3, 3), 1.0f);

					return T;
				}

				static Matrix<float> projPersp(float fov, float aspect, float cnear, float cfar)
				{
					Matrix<float> T(4, 4);

					const float tanHalfFOV = tanf(rad<float>(fov / 2.0f));

					T.setData(0, 1.0f / (tanHalfFOV * aspect));
					T.setData(5, 1.0f / tanHalfFOV);
					T.setData(10, (-cnear - cfar) / (cnear - cfar));
					T.setData(14, 2.0f * cfar * cnear / (cnear - cfar));

					return T;
				}

				static Matrix<float> view(Vector3& eye, Vector3& target, Vector3& up)
				{
					Matrix<float> orientation(4, 4);

					Vector3 zAxis = eye - target;
					zAxis.normalize();
					Vector3 xAxis = up.cross(zAxis);
					xAxis.normalize();
					Vector3 yAxis = zAxis.cross(xAxis);

					orientation.setData(orientation.index(0, 0), xAxis.x);
					orientation.setData(orientation.index(0, 1), yAxis.x);
					orientation.setData(orientation.index(0, 2), zAxis.x);

					orientation.setData(orientation.index(1, 0), xAxis.y);
					orientation.setData(orientation.index(1, 1), yAxis.y);
					orientation.setData(orientation.index(1, 2), zAxis.y);

					orientation.setData(orientation.index(2, 0), xAxis.z);
					orientation.setData(orientation.index(2, 1), yAxis.z);
					orientation.setData(orientation.index(2, 2), zAxis.z);

					Matrix<float> translation = Matrix<float>::translation(-eye);

					return orientation * translation;
				}

				T* ptr_value()
				{
					return m_data;
				}

				DEM_UINT getL() const { return m_l; }

				DEM_UINT getC() const { return m_c; }

			protected:
				DEM_UINT m_l;
				DEM_UINT m_c;
				T* m_data;
		};
	};
};

#endif