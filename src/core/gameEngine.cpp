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
	settings::fov = 45.f;
	settings::aspectRatio = 4.0f/3.0f;
	
	cameraLook.x = -0.616;
	cameraLook.y = -2.255;
	
	cameraPos = glm::vec3(4,3,3);
	
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
	instance first("a");
	util::timing::setup();
}

void gameEngine::run(){
	while(1){
		util::timing::advance();
		input();
		render();
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
	
	if(core::inputEngine::queryKey('W'))
		moveCameraF(200*util::timing::deltaTime());
	
	if(core::inputEngine::queryKey('S'))
		moveCameraF(-200*util::timing::deltaTime());
		
	if(core::inputEngine::queryKey('D'))
		moveCameraR(200*util::timing::deltaTime());
		
	if(core::inputEngine::queryKey('A'))
		moveCameraR(-200*util::timing::deltaTime());
}

void gameEngine::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto &object : instances){
		object->render();
	}
	graphics::engine::renderEngine::swapBuffers();
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

void gameEngine::moveAngles(float deltaVertical, float deltaHorizontal){
	cameraLook.x += deltaVertical;
	cameraLook.y += deltaHorizontal;
	glm::vec3 dir(std::cos(cameraLook.x) * std::sin(cameraLook.y), std::sin(cameraLook.x), std::cos(cameraLook.x) * std::cos(cameraLook.y));
	cameraDirection = dir;
	genView();
}

void gameEngine::moveCameraF(float deltaForwards){
	cameraPos += cameraDirection * deltaForwards;
	genView();
}

void gameEngine::moveCameraR(float deltaRight){
	glm::vec3 right(std::sin(cameraLook.y - M_PI/2.0f),
	                0,
					std::cos(cameraLook.y - M_PI/2.0f));
	cameraPos += right*deltaRight;
	genView();
}

void gameEngine::genView(){
	std::cout << "Camera Pos:\nX: " << cameraPos.x << "\nY: " << cameraPos.y << "\nZ:" << cameraPos.z << std::endl;
	//std::cout << "Camera Direction:\nX: " << cameraDirection.x << "\nY: " << cameraDirection.y << "\nZ:" << cameraDirection.z << std::endl;
	
	std::cout << "dV " << cameraLook.x << "   dH " << cameraLook.y << std::endl;
	glm::mat4 view = glm::lookAt(cameraPos,
	                             cameraPos + cameraDirection,
								 glm::vec3(0,1,0));
	graphics::engine::renderEngine::setViewMatrix(&view);
}

void instance::render(){
	graphics::engine::renderEngine::renderModel(modelCpuOffset, &modelMatrix);
}

instance::instance(const char* modelUuid, bool unused){
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

double M_PI = 4 * std::atan(1);

//Static reservations
std::vector<instance*> gameEngine::instances;
glm::vec3 core::engine::gameEngine::cameraPos;
glm::vec2 core::engine::gameEngine::cameraLook;
glm::vec3 core::engine::gameEngine::cameraDirection;
glm::vec3 core::engine::gameEngine::cameraRight;
float core::settings::fov;
float core::settings::aspectRatio;