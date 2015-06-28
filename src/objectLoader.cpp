#include "objectLoader.h"

void graphics::objectLoader::load(const char *objPath, const char *texPath)
{
	std::fstream objFile;
	std::string objLine;
	
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNorms;
	
	std::vector<gpuVertex> outVertices;
	
	std::size_t faces = 0;
		
	objFile.open(objPath, std::fstream::in | std::ios::binary);
	
	if(!objFile)
		core::error("Object loading failed. Could not open file at " + std::string(objPath));
	
	while(std::getline(objFile, objLine))
	{
		glm::vec3 vertex;
		glm::vec3 normal;
		glm::vec2 uv;
		
		switch(objLine[0])
		{
		case 'v':
			switch(objLine[1])
			{
			case ' ':
				std::sscanf(objLine.substr(1).c_str(), "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
				break;
				
			case 'n':
				std::sscanf(objLine.substr(2).c_str(), "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tempNorms.push_back(normal);
				break;
			
			case 't':
				std::sscanf(objLine.substr(2).c_str(), "%f %f\n", &uv.x, &uv.y);
				tempUVs.push_back(uv);
				break;
			}
			break;
			
		case 'f':
			glm::vec3 v1, v2, v3;
			std::sscanf(objLine.substr(1).c_str(),
						"%f/%f/%f %f/%f/%f %f/%f/%f\n",
						&v1.x, &v1.y, &v1.z,
						&v2.x, &v2.y, &v2.z,
						&v3.x, &v3.y, &v3.z);

			gpuVertex outV1;
			outV1.vertex = tempVertices[v1.x-1];
			outV1.uv = tempUVs[v1.y-1];
			outV1.normal = tempNorms[v1.z-1];
			
			gpuVertex outV2;
			outV2.vertex = tempVertices[v2.x-1];
			outV2.uv = tempUVs[v2.y-1];
			outV2.normal = tempNorms[v2.z-1];
			
			gpuVertex outV3;
			outV3.vertex = tempVertices[v3.x-1];
			outV3.uv = tempUVs[v3.y-1];
			outV3.normal = tempNorms[v3.z-1];
			
			outVertices.push_back(outV1);
			outVertices.push_back(outV2);
			outVertices.push_back(outV3);
			break;
		}
	}
	
	auto tempModel = new model(loadBMP(texPath), outVertices);
	graphics::engine::renderEngine::registerModel(tempModel);
}

bool test(graphics::bmpHeader& arg){
	if(arg.magic[0] == 'B' && arg.magic[1] == 'M')
		return true;
	return false;
}

GLuint graphics::objectLoader::loadBMP(const char *path){
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	std::fstream texFile;
	texFile.open(path, std::fstream::in | std::ios::binary);
	
	if(!texFile)
		core::error("Texture loading failed. Could not open file at " + std::string(path));
	
	
	std::cout << "Header " << sizeof(bmpHeader) << std::endl;
	bmpHeader header;
	texFile.read((char*)&header, sizeof(header));
	if(!test(header))
		core::error("Texture loading failed. Magic header not found for file at " + *path);
	
	BITMAPINFOHEADER dib;
	texFile.read((char*)&dib, sizeof(dib));
	
	printf("==BITMAPINFOHEADER==\n");
	printf("biSize:  %20i 0x%X\n",dib.biSize,dib.biSize);
	printf("biWidth:  %19i 0x%X\n",dib.biWidth,dib.biWidth);
	printf("biHeight:  %18i 0x%X\n",dib.biHeight,dib.biHeight);
	printf("biBitCount:  %16i 0x%X\n",dib.biBitCount,dib.biBitCount);
	printf("biSizeImage:  %15i 0x%X\n",dib.biSizeImage,dib.biSizeImage);
	
	auto width = dib.biWidth;
	auto height = dib.biHeight;
	std::size_t imageSize = (std::size_t)header.size;
	
	if(width == 0 || (width & width-1))
		core::error("Texture loading failed. Width must be a power of two and nonzero.\n"
										"Found width of " + util::itos(width) + " at path " + std::string(path));
										
	if(height == 0 || (height & height-1))
		core::error("Texture loading failed. Height must be a power of two and nonzero.\n"
										"Found height of " + util::itos(height) + " at path " + std::string(path));
	
	if(dib.biSize > (sizeof(header) + sizeof(dib)))
		texFile.seekg((dib.biSize - sizeof(header) - sizeof(dib)), std::ios_base::cur);
		
	char* texture = new char[imageSize];
	texFile.read(texture, imageSize);
	texFile.close();
	std::cout << "width " << width << std::endl;
	std::cout << "height " << height << std::endl;
	if(dib.biBitCount == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	else if (dib.biBitCount == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		
	delete texture;
	return texID;
}

void graphics::objectLoader::setup(){
	load("resources/capsule.obj", "resources/capsule0.bmp");
	graphics::engine::renderEngine::setupVertexBuffer();
	//graphics::engine::renderEngine::populateVertexBuffer();
}