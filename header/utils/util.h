#ifndef cpp_rts_util
#define cpp_rts_util

#include <string>
#include <sstream>
#include <windows.h>

namespace util{
	std::string itos(long);
	class timing{
		static long long last;
		static float freq;
		static float delta;
	public:
		static float deltaTime();
		static void advance();
		static void setup();
		static long long getFreq(){return freq;};
	};
}
#endif