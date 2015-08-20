#ifndef cpp_rts_gui
#define cpp_rts_gui

#include "all.h"
#include "graphics/font.h"
#include "util/util.h"

namespace gui
{
	namespace flat
	{
		struct fontEngine
		{
			static void setup();
		private:
			static std::vector<font> fonts;
		};
	}
}

#endif	