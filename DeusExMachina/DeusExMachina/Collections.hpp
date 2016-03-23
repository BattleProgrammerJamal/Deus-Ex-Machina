#ifndef COLLECTIONS_HPP
#define COLLECTIONS_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Types.hpp"

namespace DEM
{
	namespace Collections
	{
		template <typename T>
		struct List
		{
			public:
				List<T>(DEM_UINT capacity = 1000)
				{
					m_capacity = capacity;
					m_root = new T[capacity];
					m_size = 0;
				}

				void fetch(void(*onFetch)(T el))
				{
					if (!m_size) { return; }

					if (onFetch != 0)
					{
						for (DEM_UINT i = 0; i < m_size; ++i)
						{
							onFetch(m_root[i]);
						}
					}
				}

				DEM_UINT size() const
				{
					return m_size;
				}

				DEM_UINT capacity() const
				{
					return m_capacity;
				}

				T get(DEM_UINT index)
				{
					if (index >= 0 && index < m_size)
					{
						return m_root[index];
					}
					return 0;
				}

				void add(T el)
				{
					m_root[m_size] = el;
					m_size++;
				}

				bool find(DEM_UINT index)
				{
					return (get(index) != 0);
				}

				void remove(T *el)
				{
					for (DEM_UINT i = 0; i < m_size; ++i)
					{
						T* e = get(i);
						if (e != 0)
						{
							if (e == el)
							{
								for (DEM_UINT j = i; j < m_size - 1; ++j)
								{
									m_root[j] = m_root[j + 1];
								}
								break;
							}
						}
					}
				}

				void remove(DEM_UINT index)
				{
					for (DEM_UINT i = 0; i < m_size; ++i)
					{
						if (i == index)
						{
							for (DEM_UINT j = i; j < m_size - 1; ++j)
							{
								m_root[j] = m_root[j + 1];
							}
							break;
						}
					}
				}

				float& operator[](DEM_UINT index)
				{
					return *(&m_root[index]);
				}

			private:
				T* m_root;
				DEM_UINT m_capacity;
				DEM_UINT m_size;
		};


	};
};

#endif