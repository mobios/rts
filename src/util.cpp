#include "all.h"

std::string util::itos(long num){
	std::ostringstream ss;
	ss << num;
	return ss.str();
}

float util::timing::deltaTime(){
	return delta;
}

void util::timing::advance(){
	LARGE_INTEGER time_long;
	QueryPerformanceCounter(&time_long);
	delta = float(time_long.QuadPart - last)/freq;
	last = time_long.QuadPart;
}

void util::timing::setup(){
	LARGE_INTEGER freq_long;
	QueryPerformanceFrequency(&freq_long);
	freq = float(freq_long.QuadPart);
}

void util::parseCmd(LPSTR cmdLine){
	std::string cmdLineStr(cmdLine);
}

float util::timing::freq;
float util::timing::delta;
long long util::timing::last;