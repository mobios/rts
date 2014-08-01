#ifndef cpp_rts_objectLoader
#define cpp_rts_objectLoader

#include <string>
#include <vector>

#include "graphics/graphics.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace graphics{
	class objectLoader{
	public:
		static void load(std::string const&, std::vector<glm::vec3> &, std::vector<glm::vec2> &, std::vector<glm::vec3> &);
		static char* loadBMP(std::string &);
		static void setup();
		
	}
}

#endif