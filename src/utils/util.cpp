#include "utils\util.h"

std::string util::itos(long num){
	std::ostringstream ss;
	ss << num;
	return ss.str();
}

float util::timing::deltaTime(){
	long long time;
	LARGE_INTEGER time_long;
	QueryPerformanceCounter(&time_long);
	time = time_long.QuadPart;
	long long deltaTime = time - last;
	return float(deltaTime)/float(freq);
}

void util::timing::advance(){
	LARGE_INTEGER time_long;
	QueryPerformanceCounter(&time_long);
	last = time_long.QuadPart;
}

void util::timing::setup(){
	LARGE_INTEGER freq_long;
	QueryPerformanceFrequency(&freq_long);
	freq = freq_long.QuadPart;
}

long long util::timing::freq;
long long util::timing::last;