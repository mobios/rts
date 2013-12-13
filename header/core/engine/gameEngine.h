#ifndef cpp_rts_gameengine
#define cpp_rts_gameengine

#include <string>

namespace core{
	namespace engine{
		struct gameEngine{
			static void error(bool, std::string&);
			static void error(std::string&);
			static void glError(std::string&);
		}
	}
}

#endif