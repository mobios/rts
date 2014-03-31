#ifndef cpp_rts_renderclass
#define cpp_rts_renderclass

namespace graphics{
	struct renderClass{
		virtual void setup()=0;
		virtual void render()=0;
	}
}