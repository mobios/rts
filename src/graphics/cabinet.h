#ifndef cpp_rts_cabinet
#define cpp_rts_cabinet

#include <string>

namespace graphics{
	struct cabinet{
		std::string uuid;
		std::size_t size;
		model* models;
		
		void load(std::string&);
	}
	
	struct model{
		std::string uuid;
		std::size_t vsize;
		std::size_t tsize;
		float* normal;
		float* uv;
		float* vertex;
		char*  texture;
	}
}

#endif