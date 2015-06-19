#include "font.h"

bool font::loadFont(std::string filePath)
{

	FILE* fontFile = std::fopen(filePath.c_str(), "rb");
	if(!fontFile)
	{
		std::cerr << "Font not found at path: " << filePath << std::endl;
		std::cerr << "Source file: " << __FILE__ << std::endl;
		std::cerr << "Source line: " << __LINE__ << std::endl;

		std::fclose(fontFile);

		return false;
	}

	char h0, h1;

	std::fread(&h0, 1, 1, fontFile);
	std::fread(&h1, 1, 1, fontFile);

	if(h0 != 0xBF || h1 != 0xF2)
	{
		std::cerr << "Font at path: " << filePath << " -- is not a BFF version 2 file." <<  std::endl;
		std::cerr << "Source file: " << __FILE__ << std::endl;
		std::cerr << "Source line: " << __LINE__ << std::endl;

		std::fclose(fontFile);

		return false;
	}

	std::fread(&textureWidth, sizeof(textureWidth), 1, fontFile);
	std::fread(&textureHeight, sizeof(textureHeight), 1, fontFile);

	std::fread(&cellWidth, sizeof(cellWidth), 1, fontFile);
	std::fread(&cellHeight, sizeof(cellHeight), 1, fontFile);

	std::fread(&bitDepth, sizeof(bitDepth), 1, fontFile);

	unsigned char testOffset;
	std::fread(&testOffset, sizeof(testOffset), 1, fontFile);

	if(testOffset != 0)
	{
		std::cerr << "Font at path: " << filePath << " -- is not a BFF version 2 file." <<  std::endl;
		std::cerr << "Source file: " << __FILE__ << std::endl;
		std::cerr << "Source line: " << __LINE__ << std::endl;

		std::fclose(fontFile);

		return false;
	}


	std::fread(&widths, sizeof(unsigned char), sizeof(widths)/sizeof(unsigned char), fontFile);

	void* imgData = malloc(textureHeight*textureWidth*(bitDepth/8));
	std::fread(imgData, 1, textureHeight*textureWidth*(bitDepth/8),fontFile);


	glGenTextures(1, &textureVector);
	glBindTexture(GL_TEXTURE_2D, textureVector);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	
	switch(bitDepth)
	{
	case DEPTH_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		break;
		
	case DEPTH_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		break;
	}
	
	free(imgData);
	imgData = nullptr;
	
	return true;
}