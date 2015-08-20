#ifndef cpp_rts_util
#define cpp_rts_util

#include "all.h"

namespace util
{

	bool populateFromDirectory(std::vector<std::string>&, const char *, bool);
	
	std::string itos(long);
	
	class timing
	{
		static long long last;
		static float freq;
		static float delta;
	public:
		static float deltaTime();
		static void advance();
		static void setup();
		static long long getFreq(){return freq;};
	};
	
	void parseCmd(LPSTR);
}
#endif