#include "core/gameEngine.h"
#include "graphics/graphics.h"
#include "core/inputEngine.h"
#include "global.h"

using namespace core::engine;

LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	if(core::inputEngine::postMsg(msg, wparam, lparam))
		return 0;
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void gameEngine::error(std::string exitmsg){
	#ifdef PARAM_DEBUG
		std::cout << exitmsg;
	#else
		MessageBox(NULL, exitmsg.c_str(), "Error", MB_OK | MB_ICONERROR);
	#endif
	exit(2);
}

void gameEngine::error(bool flag, std::string exitmsg){
	if(!flag)
		error(exitmsg);
}

void gameEngine::setup(HINSTANCE hInst){
	graphics::engine::windowEngine::setup(hInst, WndProcStatic);
	graphics::engine::renderEngine::setup();
	#ifdef PARAM_DEBUG
		AllocConsole();
		HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int stdoutFhandle = _open_osfhandle((intptr_t) consoleOut, _O_TEXT);
		FILE* stdstream = _fdopen(stdoutFhandle, "w");
		*stdout = *stdstream;
		std::cout.clear();
		std::cout << "RUNNING\n";
	#endif
}

void gameEngine::run(){
	while(1){
		input();
	}
	teardown();				// Semantics
}

void gameEngine::input(){
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0, PM_REMOVE)){
		switch(msg.message){
		case WM_CLOSE:
			teardown();
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void gameEngine::teardown(int xit){
	#ifdef PARAM_DEBUG
		FreeConsole();
	#endif
	exit(xit);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	__debugMsg(Initialization);
	gameEngine::setup(hInstance);
	gameEngine::run();
}

