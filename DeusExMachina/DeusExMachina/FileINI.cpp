#include "FileINI.hpp"

using namespace DEM::Core;

FileINI::FileINI(std::string path)
	: File(path)
{
	loadDatas();
}

FileINI::~FileINI()
{
	for (FSection *section : sections)
	{
		delete section;
		section = 0;
	}
}

Resource& FileINI::loadDatas()
{
	File::load();

	sections.clear();

	m_reader.open(m_path.c_str(), std::ios::in);
	if (m_reader)
	{
		std::strstream stream;
		std::string line;
		int cpt = 0;
		while (std::getline(m_reader, line))
		{
			stream << line;
			std::vector<std::string> a = StringUtility::Split(line, '[');

			if (line.substr(0, 2) != "//" && line.substr(0, 1) != "#")
			{
				if (a.size() > 1)
				{
					sections.emplace_back(new FSection(StringUtility::PaddingRemove(line.substr(1, line.size() - 2)), std::vector<FPair*>()));
					++cpt;
				}
				else
				{
					std::vector<std::string> b = StringUtility::Split(line, '=');
					if (b.size() > 1)
					{
						sections.at(sections.size() - 1)->datas.emplace_back(new FPair(StringUtility::PaddingRemove(b.at(0)), StringUtility::PaddingRemove(b.at(1))));
					}
				}
			}
			else
			{
				comments.emplace_back(line);
			}
		}
		stream << '\0';
		m_reader.close();
	}

	return *this;
}