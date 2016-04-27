#include "FileCSV.hpp"

using namespace DEM::Core;

FileCSV::FileCSV(std::string path)
	: File(path)
{
	separator = ';';
	loadDatas();
}

FileCSV::~FileCSV()
{
}

Resource& FileCSV::loadDatas()
{
	File::load();

	datas.clear();

	m_reader.open(m_path.c_str(), std::ios::in);
	if (m_reader)
	{
		std::strstream stream;
		std::string line;
		while (std::getline(m_reader, line))
		{
			stream << line;
			std::vector<std::string> dataLine = StringUtility::Split(line, separator);

			if (line.substr(0, 2) != "//" && line.substr(0, 1) != "#")
			{
				datas.emplace_back(dataLine);
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