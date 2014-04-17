#ifndef cpp_rts_inputengine
#define cpp_rts_inputengine

#include <windows.h>
#include <windowsx.h>
#include <list>
#include <iostream>


namespace core{
	namespace input{
		struct flatMouse{
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

		struct keyObj{
			virtual void call();
			unsigned int key;
		};
		
		class settings{
			static bool raw;
			static bool hwpointer;
			
		public:
			static bool getRaw(){return raw;};
			static bool getHwpointer(){return hwpointer;};
		};
	};
	
	struct inputEngine{
		static std::list<input::flatMouse*> mouseEvents;
		static std::list<input::keyObj*> keyEvents;
		
		static bool postMsg(UINT, WPARAM, LPARAM);
		static void registerMouse(input::flatMouse*);
		static void registerKey(input::keyObj*);
		static bool isShift(){return shift;};
		static bool isCtrl(){return ctrl;};
		
		static void notifyDead(input::flatMouse*);
		static void removeKey(input::keyObj*);
		
	private:
		static void checkModify(WPARAM);
		
		static bool shift;
		static bool ctrl;
		
		static int mousex;
		static int mousey;
		
		static input::flatMouse* highlight;
	};
};
#endif