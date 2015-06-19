#ifndef cpp_rts_macro_inc
#define cpp_rts_macro_inc

#define GLM_FORCE_RADIANS
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094

#define PARAM_DEBUG

#define __loadGL(func, ptrtype) func = (ptrtype) wglGetProcAddress(#func)

#define $apptitle "rts"
#define DEBUG_SPACING std::setw(100)
#define DEBUG_FORMAT std::setiosflags(std::ios::left | std::ios::showbase | std::ios::uppercase) << std::setfill('.')

#ifdef PARAM_DEBUG
	#define __debugMsg(message) {std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << "[OK]" << std::endl;}
	#define __debugFail(message) {std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << "[FAIL]" << std::endl;}
	#define __debugVal(message, value) {std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << value << std::endl;}
	#define __debugGL(message) {auto e =glGetError(); std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << std::hex; if(e) std::cout << e; else std::cout << "[OK]"; std::cout << std::dec << std::endl;}
#else
	#define __debugMsg(message) ;
	#define __debugVal(message, value) ;
	#define __debugGL(message) ;
#endif

#endif