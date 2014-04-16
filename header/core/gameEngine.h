#ifndef cpp_rts_gameengine
#define cpp_rts_gameengine

#include <string>
#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

namespace core{
	namespace engine{
		class gameEngine{
			static HINSTANCE hInstance;
		public:
			static void error(bool, std::string);
			static void error(std::string);
			static void setup(HINSTANCE);
			static void run();
			static void input();
			static void teardown(int xit = 0);
		};
	}
}

#endif