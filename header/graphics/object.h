#ifndef cpp_rts_object
#define cpp_rts_object

#include "graphics/renderable.h"

namespace graphics{
	struct object{
		gluint VAO;
		gluint VBO;
		gluint VIBO;
		
		virtual void render();
	}
}