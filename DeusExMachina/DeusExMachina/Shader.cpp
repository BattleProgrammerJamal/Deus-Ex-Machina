#include "Shader.hpp"

using namespace DEM::Core;

Shader::Shader(std::string vs, std::string fs)
{
	m_pathVS = vs;
	m_pathFS = fs;
	m_vs = 0;
	m_fs = 0;
	m_gs = 0;
	m_ts = 0;
}

Shader::~Shader()
{
	glDetachShader(m_program, m_vs);
	glDetachShader(m_program, m_fs);
	glDetachShader(m_program, m_gs);
	glDetachShader(m_program, m_ts);
	glDeleteProgram(m_program);
	glDeleteShader(m_vs);
	glDeleteShader(m_fs);
	glDeleteShader(m_gs);
	glDeleteShader(m_ts);
}

Resource& Shader::load()
{
	File stream(m_pathVS);
	const char* vsText = stream.cReadAll();
	GLint vsSize = strlen(vsText);
	stream.setPath(m_pathFS);
	const char* fsText = stream.cReadAll();
	GLint fsSize = strlen(fsText);

	GLint success;

	m_vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vs, 1, &vsText, &vsSize);
	glCompileShader(m_vs);
	glGetShaderiv(m_vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(m_vs, sizeof(infoLog), 0, infoLog);
		std::cerr << "Error on Vertex Shader compilation : " << infoLog << std::endl;
	}

	m_fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fs, 1, &fsText, &fsSize);
	glCompileShader(m_fs);
	glGetShaderiv(m_fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(m_fs, sizeof(infoLog), 0, infoLog);
		std::cerr << "Error on Fragment Shader compilation : " << infoLog << std::endl;
	}

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vs);
	glAttachShader(m_program, m_fs);

	glLinkProgram(m_program);

	glGetProgramiv(m_fs, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		GLchar infoLog[1024];
		glGetProgramInfoLog(m_fs, sizeof(infoLog), 0, infoLog);
		std::cerr << "Error on Shader Program linkage : " << infoLog << std::endl;
	}

	glValidateProgram(m_program);

	return *this;
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

GLuint Shader::getProgram() const
{
	return m_program;
}