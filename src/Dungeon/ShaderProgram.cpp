#include "Dungeon/ShaderProgram.hpp"

#include <fstream>

namespace Dungeon
{
	INTERNAL std::string stringFromFile(const std::string &filename)
	{
		std::ifstream file;
		file.open(filename.c_str(), std::ios::in | std::ios::binary);

		std::string output;
		std::string line;

		if (!file.is_open())
		{
			std::runtime_error(std::string("Failed to open file: ") + filename);
		}
		else
		{
			while (file.good())
			{
				getline(file, line);

				output.append(line + "\n");
			}
		}

		file.close();
		return output;
	}

	ShaderProgram::ShaderProgram()
		: m_program(0)
		, m_linked(false)
		, m_errorLog()
	{
		m_program = glCreateProgram();
	}
	ShaderProgram::~ShaderProgram()
	{
		if (m_program)
			glDeleteProgram(m_program);
	}

	bool ShaderProgram::attachShaderFromFile(ShaderType type, const std::string &filename)
	{
		std::string source = stringFromFile(filename);
		return attachShaderFromMemory(type, source);
	}
	bool ShaderProgram::attachShaderFromMemory(ShaderType type, const std::string &source)
	{
		if (!m_program)
			m_program = glCreateProgram();

		const char* shaderSource = source.c_str();

		GLuint shader;
		if (type == ShaderType::Vertex)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else if (type == ShaderType::Fragment)
			shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &shaderSource, nullptr);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Compile failure in shader:\n");

			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			char *infoLog = new char[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
			msg.append(infoLog);
			delete[] infoLog;

			msg.append("\n");
			m_errorLog.append(msg);

			glDeleteShader(shader);

			return false;
		}

		glAttachShader(m_program, shader);

		return true;
	}

	void ShaderProgram::use() const
	{
		if (!isInUse())
			glUseProgram(m_program);
	}
	bool ShaderProgram::isInUse() const
	{
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

		return currentProgram == (GLint)m_program;
	}
	void ShaderProgram::stopUsing() const
	{
		if (isInUse())
			glUseProgram(0);
	}

	bool ShaderProgram::link()
	{
		if (!m_program)
			m_program = glCreateProgram();

		if (!isLinked())
		{
			glLinkProgram(m_program);

			GLint status;
			glGetProgramiv(m_program, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				std::string msg("Program linking failure:\n");
				
				GLint infoLogLength;
				glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
				
				char *infoLog = new char[infoLogLength + 1];
				glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog);
				msg.append(infoLog);
				delete[] infoLog;

				glDeleteProgram(m_program);
				m_program = 0;

				msg.append("\n");
				m_errorLog.append(msg);

				glDeleteProgram(m_program);
				m_program = 0;

				m_linked = false;
				return m_linked;
			}

			m_linked = true;
		}

		return m_linked;
	}

	void ShaderProgram::bindAttribLocation(GLuint location, const GLchar *name)
	{
		glBindAttribLocation(m_program, location, name);
	}

	GLint ShaderProgram::getAttribLocation(const GLchar *name)
	{
		return glGetAttribLocation(m_program, name);
	}
	GLint ShaderProgram::getUniformLocation(const GLchar *name)
	{
		return glGetUniformLocation(m_program, name);
	}

	void ShaderProgram::setUniform(const GLchar *name, float x)
	{
		if (!isInUse())
			use();

		glUniform1f(getUniformLocation(name), x);
	}
	void ShaderProgram::setUniform(const GLchar *name, float x, float y)
	{
		if (!isInUse())
			use();

		glUniform2f(getUniformLocation(name), x, y);
	}
	void ShaderProgram::setUniform(const GLchar *name, float x, float y, float z)
	{
		if (!isInUse())
			use();

		glUniform3f(getUniformLocation(name), x, y ,z);
	}
	void ShaderProgram::setUniform(const GLchar *name, float x, float y, float z, float w)
	{
		if (!isInUse())
			use();

		glUniform4f(getUniformLocation(name), x, y, z, w);
	}
	void ShaderProgram::setUniform(const GLchar *name, unsigned int x)
	{
		if (!isInUse())
			use();

		glUniform1ui(getUniformLocation(name), x);
	}
	void ShaderProgram::setUniform(const GLchar *name, int x)
	{
		if (!isInUse())
			use();

		glUniform1i(getUniformLocation(name), x);
	}
	void ShaderProgram::setUniform(const GLchar *name, bool x)
	{
		if (!isInUse())
			use();

		glUniform1i(getUniformLocation(name), x);
	}
}