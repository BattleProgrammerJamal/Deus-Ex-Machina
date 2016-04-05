#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Resource.hpp"

namespace DEM
{
	namespace Core
	{
		class File : public Resource
		{
			public:
				File(std::string path);
				virtual ~File();

				Resource& load();

				std::string getPath() const;

				void setPath(const std::string& path);

				std::string readAll();

				char* cReadAll();

				File& write(const std::string& buff);

			private:
				std::string		m_path;
				std::ofstream	m_writter;
				std::ifstream	m_reader;
		};
	};
};

#endif