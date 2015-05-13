#include "all.h"

bool font::loadFont(std::string filePath)
{

	FILE* fontFile = std::fopen(filePath, "rb");
	if(!fontFile)
	{
		std::cerr << "Font not found at path: " << filePath << std::endl;
		std::cerr << "Source file: " << __FILE__ << std::endl;
		std::cerr << "Source line: " << __LINE__ << std::endl;

		std::fclose(filePath);

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

		std::fclose(filePath);

		return false;
	}

	std::fread(&textureWidth, sizeof(textureWidth), 1, fontFile);
	std::fread(&textureHeight, sizeof(textureHeight), 1, fontFile);

	std::fread(&cellWidth, sizeof(cellWidth), 1, fontFile);
	std::fread(&cellHeight, sizeof(cellHeight), 1, fontFile);

	std::fread(&bitDetph, sizeof(bitDetph), 1, fontFile);

	unsigned char testOffset;
	std::fread(&testOffset, sizeof(testOffset), 1, fontFile);

	if(testOffset != 0)
	{
		std::cerr << "Font at path: " << filePath << " -- is not a BFF version 2 file." <<  std::endl;
		std::cerr << "Source file: " << __FILE__ << std::endl;
		std::cerr << "Source line: " << __LINE__ << std::endl;

		std::fclose(filePath);

		return false;
	}


	std::fread(&widths, sizeof(unsigned char), sizeof(widths)/sizeof(unsigned char), fontFile);

	void* imgData = malloc(textureHeight*textureWidth*(bitDetph/8));
	std::fread(imgData, 1, textureHeight*textureWidth*(bitDetph/8),filePath);


	glGenTextures(&textureVector, 1);
	glBindTexture(GL_TEXTURE_2D, textureVector);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}