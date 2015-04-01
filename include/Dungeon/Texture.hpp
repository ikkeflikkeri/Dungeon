#ifndef DUNGEON_TEXTURE_HPP
#define DUNGEON_TEXTURE_HPP

#include <Dungeon/OpenGL.hpp>
#include <Dungeon/NonCopyable.hpp>
#include <Dungeon/Image.hpp>

namespace Dungeon
{
	class Texture : public NonCopyable
	{
	public:
		Texture();
		Texture(const Image& image, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
		virtual ~Texture();

		bool loadFromFile(const char* filename, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
		bool loadFromImage(const Image& image, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);


		void bind(GLuint position);

		inline GLuint getObject() const { return m_object; }
		inline GLfloat getWidth() const { return m_width; }
		inline GLfloat getHeight() const { return m_height; }

	private:
		GLuint m_object;
		GLfloat m_width;
		GLfloat m_height;
	};
}

#endif