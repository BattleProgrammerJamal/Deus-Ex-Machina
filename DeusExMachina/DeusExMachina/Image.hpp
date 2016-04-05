#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "STB/stb_image.h"

#include "Resource.hpp"

namespace DEM
{
	namespace Core
	{
		class Image : public Resource
		{
			public:
				Image(const std::string& path = "");
				virtual ~Image();

				Resource& load();

				DEM_UCHAR* getDatas() const;

				int getWidth() const;
				
				int getHeight() const;

				int getComp() const;

				std::string getPath() const;
				void setPath(const std::string& path);

				bool isLoaded() const;

			private:
				DEM_UCHAR*		m_data;
				int				m_width;
				int				m_height;
				int				m_comp;
				std::string		m_path;
				bool			m_loaded;
		};
	};
};

#endif