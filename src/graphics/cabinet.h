#ifndef cpp_rts_cabinet
#define cpp_rts_cabinet

#include <string>

namespace graphics{
	struct cabinet{
		std::string uuid;
		
	}
	
	struct model{
		std::string uuid;
		int vsize;
		float* normal;
		float* uv;
		float* vertex;
	}
}

#endif