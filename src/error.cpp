#include "error.h"

extern TRIGGER engineTeardown;

void core::error(std::string exitmsg)
{
	MessageBox(NULL, exitmsg.c_str(), "Error", MB_OK | MB_ICONERROR);
	engineTeardown();
	exit(-1);
}


void core::error(bool flag, std::string exitmsg)
{
	if(!flag)
		error(exitmsg);
}