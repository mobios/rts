#ifndef cpp_rts_inputengine
#define cpp_rts_inputengine

#include "all.h"
#include "core/error.h"
#include "graphics/graphics.h"


namespace core
{
	namespace input
	{
		struct flatMouse
		{
			virtual void over();
			virtual void out();
			virtual void down_l();
			virtual void up_l();
			virtual void down_r();
			virtual void up_r();
			
			float x;
			float y;
			float xsize;
			float ysize;
			
			bool inbounds(signed short x, signed short y);
		};
		
		struct settings{
			static bool raw;
			static bool hwpointer;
			static bool captureMouse;
			static bool getRaw(){return raw;};
			static bool getHwpointer(){return hwpointer;};
		};
	};
	
	struct inputEngine
	{
		static std::list<input::flatMouse*> mouseEvents;
		
		static void setup();
		static bool postMsg(UINT, WPARAM, LPARAM);
		static void registerMouse(input::flatMouse*);
		static void registerMouseMovement(mouseMovementMessage);
		
		static bool isShift(){return shift;};
		static bool isCtrl(){return ctrl;};
		static bool queryKey(unsigned char);
		
		static void notifyDead(input::flatMouse*);
		static void centerCursor();
		
	private:
		static void checkModify(WPARAM);
		
		static bool shift;
		static bool ctrl;
		static bool moved;
		
		static int mousex;
		static int mousey;
		
		static mouseMovementMessage mouseMovementCallback;
		static input::flatMouse* highlight;
		
		static bool keys[256];
	};
};
#endif