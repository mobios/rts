#ifndef cpp_rts_objectLoader
#define cpp_rts_objectLoader

#include "all.h"
#include "util/util.h"
#include "graphics/graphics.h"
#include "core/error.h"

namespace util
{
	class loader
	{
	public:
		static void load(const char *, const char *);
		static GLuint loadBMP(const char *);
		static void setup();
	};
	
	#pragma pack(push)
	#pragma pack(1)
	struct __attribute__ ((packed)) bmpHeader
	{
		char magic[2];
		int32_t size;
		int32_t reserved;
		int32_t offset;
	};
	#pragma pack(pop)

}

#endif