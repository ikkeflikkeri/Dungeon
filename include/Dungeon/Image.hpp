#ifndef DUNGEON_IMAGE_HPP
#define DUNGEON_IMAGE_HPP

#include <Dungeon/Types.hpp>

namespace Dungeon
{
	class Image
	{
	public:
		enum Format
		{
			Format_Greyscale = 1,
			Format_GreyscaleAlpha = 2,
			Format_RGB = 3,
			Format_RGBA = 4,
		};

		Image();
		Image(UInt32 width, UInt32 height, Format format, const UInt8 *pixels = nullptr);
		Image(const Image &other);
		~Image();

		Image& operator=(const Image &other);

		bool loadFromFile(const char *filename);
		bool loadFromMemory(UInt32 width, UInt32 height, Format format, const UInt8 *pixels);

		inline UInt32 getWidth() const { return m_width; }
		inline UInt32 getHeight() const { return m_height; }
		inline Format getFormat() const { return m_format; }
		inline UInt8* getPixelPtr() const { return m_pixels; }

		UInt8* getPixel(UInt32 column, UInt32 row) const;
		void setPixel(UInt32 column, UInt32 row, const UInt32 *pixel);

		void flipVertically();

	private:
		Format m_format;
		UInt32 m_width;
		UInt32 m_height;
		UInt8* m_pixels;
	};
}

#endif