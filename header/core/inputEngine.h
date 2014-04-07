#ifndef cpp_rts_inputengine
#define cpp_rts_inputengine

#include <vector>
#include <windows>

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
			virtual void call;
			unsigned int key;
		}
		
		struct inputEngine{
			static void std::vector<flatMouse> mouseEvents;
			static void std::vector<keyObj> keyEvents;
			
			static MSG postMsg(MSG);
			static void registerMouse(flatMouse*);
			static void registerKey(keyObj*);
			static void bound(unsigned int);
			static bool isShift(){return shift;};
			static bool isCtrl(){return ctrl;};
			
		private:
			static void checkModify(WPARAM);
			
			static bool shift;
			static bool ctrl;
			
			static int mousex;
			static int mousey;
		}
		
		class settings{
			static bool raw;
			static bool hwpointer;
			
	}
}