#ifndef cpp_rts_font
#define cpp_rts_font

#include "all.h"

struct font
{
	unsigned int textureHeight, textureWidth;
	unsigned int cellHeight, cellWidth;
	unsigned char widths[256];
	unsigned char bitDepth;

	std::size_t firstCharOffset;

	GLuint textureVector;

	bool loadFont(std::string);
};

#endif
