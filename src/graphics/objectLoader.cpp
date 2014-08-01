#include "graphics/objectLoader.h"
#include "fstream"
#include <cstdio>

void graphics::objectLoader::load(std::string &objPath, std::string &texPath){
	std::fstream objFile;
	std::string objLine;
	
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNorms;
	
	std::vector<glm::vec3> vertices;
	
	std::size_t faces = 0;
		
	objFile.open(objPath.c_str(), std::fstream::in);
	
	if(!objFile)
		core::engine::gameEngine::error("Object loading failed. Could not open file at " + path);
	
	while(std::getline(objFile, objLine)){
		switch(objLine[0]){
		case 'v':
			switch(objLine[1]){
			case ' ':
				glm::vec3 vertex;
				std::sscanf(objLine.substr(1).c_str(), "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
				break;
				
			case 'vn':
				glm::vec3 normal;
				std::sscanf(objLine.substr(2).c_str(), "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tempNorms.push_back(normal);
				break;
			
			case 'vt':
				glm::vec2 uv;
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
			
			v1.x = tempVertices[v1.x];
			v1.y = tempUVs[v1.y];
			v1.z = tempNorms[v1.z];		
			
			v2.x = tempVertices[v2.x];
			v2.y = tempUVs[v2.y];
			v2.z = tempNorms[v2.z];	
			
			v3.x = tempVertices[v3.x];
			v3.y = tempUVs[v3.y];
			v3.z = tempNorms[v3.z];
			
			vertices.push_back(v1);
			vertices.push_back(v2);
			vertices.push_back(v3);
			break;
		}
	}
	
	std::size_t mdi = 0; //modelDataIterator
	std::size_t modelDataFSize = vertices.size()*(3+2+3);
	float* modelData = new float[modelDataFSize];
	
	for(glm::vec3 &vertex : vertices){
		modelData[mdi] = vertices.x.x;
		modelData[mdi+1] = vertices.x.y;
		modelData[mdi+2] = vertices.x.z;
		mdi+=3;
		
		modelData[mdi] = vertices.y.x;
		modelData[mdi+1] = vertices.y.y;
		mdi+=2;
		
		modelData[mdi] = vertices.z.x;
		modelData[mdi+1] = vertices.z.y;
		modelData[mdi+2] = vertices.z.z;
		mdi+=3;
	}
	
}

void graphics::objectLoader::loadBMP(std::string &path){
	std::fstream texFile;
	texFile.open(path.c_str(), std::fstream::in);
	
	if(!texFile)
		core::engine::gameEngine::error("Texture loading failed. Could not open file at " + path);
		
	unsigned char header[54];
	texFile.read(header, 54);
	if(header[0] != 'B' || header[1] != 'M')
		core::engine::gameEngine::error("Texture loading failed. Magic header not found for file at " + path);
		
	unsigned int dataOffset = *(int*)&(header[0x0A]);
	unsigned int width = *(int*)&(header[0x12]);
	unsigned int height = *(int*)&(header[0x16]);
	unsigned int imageSize = *(int*)&(header[0x22]);
	
	if(width = 0 || (width & width-1))
		core::engine::gameEngine::error("Texture loading failed. Width must be a power of two and nonzero.\
										 found width of " + width + " at path " + path);
										
	if(height = 0 || (height & height-1))
		core::engine::gameEngine::error("Texture loading failed. Height must be a power of two and nonzero.\
										 found height of " + height + " at path " + path);
	
	imageSize = imageSize ? imageSize : width * height *3;
	dataOffset = dataOffset ? dataOffset : 54;
	
	unsigned char* texture = new unsigned char[imageSize];
	texFile.read(texture, imageSize);
	texFile.close();
	
	return texture;
}

void graphics::objectLoader::load(){
	
}