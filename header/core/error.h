#ifndef cpp_rts_error
#define cpp_rts_error

#include "all.h"

namespace core
{
	void error(bool flag, std::string);
	void error(std::string) __attribute__((noreturn));
}


#endif