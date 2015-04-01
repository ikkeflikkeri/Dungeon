#ifndef DUNGEON_SHADERPROGRAM_HPP
#define DUNGEON_SHADERPROGRAM_HPP

#include <Dungeon/Common.hpp>
#include <Dungeon/NonCopyable.hpp>

#include <Dungeon/OpenGL.hpp>

#include <string>

namespace Dungeon
{
	enum class ShaderType
	{
		Vertex,
		Fragment
	};

	class ShaderProgram : public NonCopyable
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		bool attachShaderFromFile(ShaderType type, const std::string &filename);
		bool attachShaderFromMemory(ShaderType type, const std::string &source);

		void use() const;
		bool isInUse() const;
		void stopUsing() const;

		bool link();
		inline bool isLinked() const { return m_linked; };

		void bindAttribLocation(GLuint location, const GLchar *name);

		GLint getAttribLocation(const GLchar *name);
		GLint getUniformLocation(const GLchar *name);

		void setUniform(const GLchar *name, float x);
		void setUniform(const GLchar *name, float x, float y);
		void setUniform(const GLchar *name, float x, float y, float z);
		void setUniform(const GLchar *name, float x, float y, float z, float w);
		void setUniform(const GLchar *name, unsigned int x);
		void setUniform(const GLchar *name, int x);
		void setUniform(const GLchar *name, bool x);

		inline GLuint getProgram() const { return m_program; }
		inline const std::string &getErrorLog() const { return m_errorLog; }

	private:
		GLuint m_program;
		bool m_linked;
		std::string m_errorLog;
	};
}

#endif