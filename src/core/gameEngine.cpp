#include "core/gameEngine.h"
#include "graphics/graphics.h"
#include "global.h"
#include <iostream>

using namespace core::engine;

LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
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
}

void gameEngine::run(){
	while(1){
		input();
	}
}

void gameEngine::input(){
	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		switch(msg){
			
		TranslateMessage(&msg);
		

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	__debugMsg(Initialization);
	gameEngine::setup(hInstance);
	gameEngine::run();
}

