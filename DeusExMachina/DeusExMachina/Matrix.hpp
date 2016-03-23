#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cmath>
#include <strstream>
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

			private:
				DEM_UINT m_l;
				DEM_UINT m_c;
				T* m_data;
		};
	};
};

#endif