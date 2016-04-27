#ifndef FILE_INI_HPP
#define FILE_INI_HPP

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
		class FileINI : public File
		{
			public:
				struct FPair
				{
					std::string key;
					std::string value;

					FPair(const std::string& key, const std::string& value)
					{
						this->key = key;
						this->value = value;
					}
				};

				struct FSection
				{
					std::string name;
					std::vector<FPair*> datas;

					FSection(std::string name, std::vector<FPair*> datas)
					{
						this->name = name;
						this->datas = datas;
					}

					~FSection()
					{
						for (FPair *pair : datas)
						{
							delete pair;
							pair = 0;
						}
					}

					FPair* getByKey(const std::string& key)
					{
						for (FPair *pair : datas)
						{
							if (pair->key == key)
							{
								return pair;
							}
						}
						return 0;
					}
				};

				std::vector<FSection*> sections;
				std::vector<std::string> comments;

				FileINI(std::string path);
				virtual ~FileINI();

				Resource& loadDatas();

				DEM_UINT size() const
				{
					return sections.size();
				}

				std::vector<FPair*> operator[](const std::string& name)
				{
					for (FSection *section : sections)
					{
						if (section->name == name)
						{
							return section->datas;
						}
					}
					return std::vector<FPair*>();
				}
		};
	};
};

#endif