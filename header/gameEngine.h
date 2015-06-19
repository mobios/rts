#ifndef cpp_rts_gameengine
#define cpp_rts_gameengine

#include "all.h"
#include "inputEngine.h"
#include "graphics.h"
#include "util.h"

// extern double M_PI;

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
			static void error(std::string) __attribute__((noreturn));
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