#include "core/gameEngine.h"
#include "graphics/graphics.h"
#include "core/inputEngine.h"
#include "global.h"
#define PARAM_DEBUG

using namespace core::engine;

LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	if(core::inputEngine::postMsg(msg, wparam, lparam))
		return 0;
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void gameEngine::error(std::string exitmsg){
	#ifdef PARAM_DEBUG
		std::cout << exitmsg;
		asm ("int3");
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
	settings::fov = 90.f;
	settings::aspectRatio = 4.0f/3.0f;
	#ifdef PARAM_DEBUG
		AllocConsole();
		HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int stdoutFhandle = _open_osfhandle((intptr_t) consoleOut, _O_TEXT);
		FILE* stdstream = _fdopen(stdoutFhandle, "w");
		*stdout = *stdstream;
		std::cout.clear();
		std::cout << "RUNNING\n";
	#endif
	graphics::engine::windowEngine::setup(hInst, WndProcStatic);
	graphics::engine::renderEngine::setup();
	std::cout <<"Sizeof gpuVertex: " << sizeof(graphics::gpuVertex) << std::string("\nSizeof sequential glm::vec; ") << sizeof(glm::vec3)*2 + sizeof(glm::vec2); 
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
		case WM_DESTROY:
		case WM_CLOSE:
			std::cout << "teardown\n";
			teardown();
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void gameEngine::registerInstance(instance* instanceParam){
	instances.push_back(instanceParam);
}

void gameEngine::teardown(int xit){
	#ifdef PARAM_DEBUG
		FreeConsole();
	#endif
	exit(xit);
}

instance::instance(std::string* modelUuid, bool unused){
	modelCpuOffset = graphics::engine::renderEngine::lookupModel(modelUuid);
	modelMatrix = glm::mat4(1.0f);
	dynamic = true;
	instanceVectorOffset = -1;
	gameEngine::registerInstance(new instance(*this));
	dynamic = false;	
}

instance::~instance(){
	if(dynamic)
		delete this;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	__debugMsg(Initialization);
	gameEngine::setup(hInstance);
	gameEngine::run();
}

//Static reservations
std::vector<instance*> gameEngine::instances;
float core::settings::fov;
float core::settings::aspectRatio;