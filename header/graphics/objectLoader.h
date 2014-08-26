#ifndef cpp_rts_objectLoader
#define cpp_rts_objectLoader

#include "graphics/graphics.h"
#include "core/gameEngine.h"
#include "utils/util.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include <string>
#include <vector>
#include <fstream>

#include <cstdint>

namespace graphics{
	class objectLoader{
	public:
		static void load(const char *, const char *);
		static GLuint loadBMP(const char *);
		static void setup();
	};
	
	struct __attribute__ ((packed)) bmpHeader{
		char magic[2];
		int32_t size;
		int32_t reserved;
		int32_t offset;
		
		bool test();
	};

}

#endif