#include "File.hpp"

using namespace DEM::Core;

File::File(std::string path)
	 : Resource()
{
	m_path = path;
}

File::~File()
{
	if (m_reader.is_open())
	{
		m_reader.close();
	}

	if (m_writter.is_open())
	{
		m_writter.close();
	}
}

Resource& File::load()
{
	return *this;
}

std::string File::getPath() const
{
	return m_path;
}

void File::setPath(const std::string& path)
{
	m_path = path;
}

std::string File::readAll()
{
	m_reader.open(m_path.c_str(), std::ios::in);
	if (m_reader)
	{
		std::strstream stream;
		std::string line;
		while (std::getline(m_reader, line))
		{
			stream << line;
		}
		stream << '\0';
		m_reader.close();
		return stream.str();
	}
	return "";
}

char* File::cReadAll()
{
	char* text = 0;

	if (!m_path.empty())
	{
		FILE *file;
		fopen_s(&file, m_path.c_str(), "r");

		if (file != 0)
		{
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);

			if (count > 0)
			{
				text = (char*)malloc(count + 1);
				count = (int)fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}

			fclose(file);
		}
	}

	return text;
}

File& File::write(const std::string& buff)
{
	m_writter.open(m_path.c_str(), std::ios::out | std::ios::app);
	if (m_writter)
	{
		m_writter << buff;
		m_writter.close();
	}
	return *this;
}