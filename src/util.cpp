#include "util.h"

bool util::populateFromDirectory(std::vector<std::string>& destination, const char * path, bool recurse)
{
	WIN32_FIND_DATA findData;
	HANDLE findHandle;
	
	findHandle = FindFirstFile(path, &findData);
	if(findHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Could not populate a directory listing at: " << path << std::endl;
		std::cout << "Microsoft Windows error code: " << GetLastError() << std::endl;
		return false;
	}
	
	do
	{
		if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::cout << "Directory in directory: " << findData.cFileName << std::endl;
		}
		else
		{
			std::cout << "File in directory: " << findData.cFileName << std::endl;
		}
	}
	while(FindNextFile(findHandle, &findData));
	
	DWORD dwError = GetLastError();
	if(dwError != ERROR_NO_MORE_FILES)
	{
		std::cout << "Error populating directory listing at: " << path << std::endl;
		std::cout << "Microsoft Windows error code: " << GetLastError() << std::endl;
		return false;
	}
	
	FindClose(findHandle);
	
	return true;
}


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