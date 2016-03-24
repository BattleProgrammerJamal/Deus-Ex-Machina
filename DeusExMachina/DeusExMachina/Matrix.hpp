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
				Matrix(DEM_UINT L, DEM_UINT C)
				{
					m_l = L;
					m_c = C;
					m_data = new T[m_l * m_c];
					zero();
				}

				Matrix(const Matrix<T>& m)
				{
					m_l = m.m_l;
					m_c = m.m_c;
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
					T.identity();
					return T;
				}

				static Matrix<float> rotation(const Quaternion& q)
				{
					Matrix<float> T(4, 4);
					T.identity();
					return T;
				}

				static Matrix<float> scale(const Vector3& v)
				{
					Matrix<float> T(4, 4);
					T.identity();
					return T;
				}

				static Matrix<float> projOrtho(DEM_UINT left, DEM_UINT right, DEM_UINT top, DEM_UINT down, float cnear, float cfar)
				{
					Matrix<float> T(4, 4);
					T.identity();
					return T;
				}

				static Matrix<float> projPersp(float fov, float aspect, float cnear, float cfar)
				{
					Matrix<float> T(4, 4);
					T.identity();
					return T;
				}

				static Matrix<float> view(const Vector3& eye, const Vector3& target, const Vector3& up)
				{
					Matrix<float> T(4, 4);
					T.identity();
					return T;
				}

			private:
				DEM_UINT m_l;
				DEM_UINT m_c;
				T* m_data;
		};
	};
};

#endif