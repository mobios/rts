#ifndef cpp_rts_gameengine
#define cpp_rts_gameengine

#include "glm/glm.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#undef __STRICT_ANSI__
#include <cstdio>
#define __STRICT_ANSI__

namespace core{
	namespace engine{
		struct instance;
		
		class gameEngine{
			static HINSTANCE hInstance;
			static std::vector<instance*> instances;
				
		public:
			static void error(bool, std::string);
			static void error(std::string);
			static void setup(HINSTANCE);
			static void run();
			static void input();
			static void registerInstance(instance*);
			static void teardown(int xit = 0);
		};
		
		struct instance{
			glm::mat4 modelMatrix;
			std::size_t modelCpuOffset;
			std::size_t instanceVectorOffset;
			
			instance(std::string*, bool unused = false);
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