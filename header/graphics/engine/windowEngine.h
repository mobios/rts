#ifndef cpp_rts_windowengine
#define cpp_rts_windowengine

#include <windows.h>

namespace graphics{
	namespace engine{
		struct windowEngine{
			static HWND hWnd;
			static HDC hDC;
			
			static WNDCLASS* genWndClass(const HINSTANCE, const WNDPORC, const LPCSTR) const;
			static bool bindWndClass(WNDCLASS*);
			static bool createWindow(const HINSTANCE, const WNDPROC);
			static void makeAvailable();
			static HDC getHDC();
			static HWND getHWND();
		}
	}
}

#endif			