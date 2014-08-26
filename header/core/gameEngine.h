#ifndef cpp_rts_gameengine
#define cpp_rts_gameengine

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#undef __STRICT_ANSI__
#include "utils/util.h"
#include <cstdio>
#include <cmath>
#define __STRICT_ANSI__

extern double M_PI;

namespace core{
	namespace engine{
		struct instance;
		
		class gameEngine{
			static HINSTANCE hInstance;
			static std::vector<instance*> instances;
			static glm::vec3 cameraPos;
			static glm::vec2 cameraLook;
			static glm::vec3 cameraDirection;
			static glm::vec3 cameraRight;
			
			static float deltaTime;
			
		public:
			static void error(bool, std::string);
			static void error(std::string);
			static void setup(HINSTANCE);
			static void run();
			static void input();
			static void render();
			static void registerInstance(instance*);
			static void teardown(int xit = 0);
			
			static glm::vec3* getCameraPos(){return &cameraPos;};
			static glm::vec2* getCameraLook(){return &cameraLook;};
			
			static void moveAngles(float, float);
			static void moveCameraF(float);
			static void moveCameraR(float);
			static void genView();
		};
		
		struct instance{
			glm::mat4 modelMatrix;
			std::size_t modelCpuOffset;
			std::size_t instanceVectorOffset;
			
			void render();
			
			instance(const char*, bool unused = false);
			~instance();
		private:
			bool dynamic;
		};
	}
	
	struct settings{
		static float fov;
		static float aspectRatio;
	};
}

#endif