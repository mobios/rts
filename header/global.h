#ifndef cpp_rts_global
#define cpp_rts_global

#include <iomanip>
#include <iostream>

#define $apptitle "rts"
#define DEBUG_SPACING std::setw(100)
#define DEBUG_FORMAT std::setiosflags(std::ios::left | std::ios::showbase | std::ios::uppercase) << std::setfill('.')
#define PARAM_DEBUG
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