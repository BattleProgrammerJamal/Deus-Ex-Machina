#ifndef FILE_CSV_HPP
#define FILE_CSV_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <strstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Types.hpp"

#include "File.hpp"

namespace DEM
{
	namespace Core
	{
		class FileCSV : public File
		{
			public:
				char separator;

				std::vector<std::vector<std::string> > datas;
				std::vector<std::string> comments;

				FileCSV(std::string path);
				virtual ~FileCSV();

				Resource& loadDatas();

				DEM_UINT size() const
				{
					return datas.size();
				}

				std::vector<std::string> operator[](DEM_UINT index)
				{
					if (index < datas.size() && index != 0)
					{
						return datas.at(index);
					}
					return std::vector<std::string>();
				}
		};
	};
};

#endif