#include "graphics/graphics.h"
#include "graphics/glWrapper.h"
#include "core/gameEngine.h"
#include "global.h"
#include <iostream>

using namespace graphics::engine;

void windowEngine::setup(const HINSTANCE hInst, const WNDPROC WndProc){
	createWindow(hInst, WndProc);
	__debugMsg(Window creation);
}

WNDCLASS* windowEngine::genWndClass(const HINSTANCE hInstance,
										   const WNDPROC WndProc,
										   const LPCSTR className){
										   
	WNDCLASS* wc = new WNDCLASS();
	wc->style = CS_HREDRAW | CS_VREDRAW |CS_OWNDC;
	wc->lpfnWndProc = WndProc;
	wc->cbClsExtra =0;
	wc->cbWndExtra =0;
	wc->hInstance = hInstance;
	wc->hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc->hCursor = LoadCursor(NULL, IDC_ARROW);
	wc->lpszMenuName = NULL;
	wc->lpszClassName = className;
	
	return wc;
}

bool windowEngine::bindWndClass(WNDCLASS* WndClass){
	WNDCLASS wc = *WndClass;
	delete WndClass;
	WndClass = NULL;
	return RegisterClass(&wc);
}

bool windowEngine::createWindow(HINSTANCE hInstance, WNDPROC wndProc){
	core::engine::gameEngine::error(bindWndClass(genWndClass(hInstance, wndProc, $apptitle)), 
												 "Unable to register window class.");
		  
	hWnd = CreateWindow( $apptitle,
						 $apptitle,
						 WS_OVERLAPPEDWINDOW,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 NULL,
						 NULL,
						 hInstance,
						 NULL);
						 
	core::engine::gameEngine::error(hWnd, "Unable to create window.");
	
	hDC = GetDC(hWnd);
	__debugVal(hDC at generation, hDC);
	core::engine::gameEngine::error(hDC, "Unable to fetch device context.");
	makeAvailable();
}

void windowEngine::makeAvailable(){
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}

void renderEngine::makeOldContext(){
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(*hDC, &pfd);
	core::engine::gameEngine::error(nPixelFormat, "Unable to choose pixel format.");
	
	core::engine::gameEngine::error(SetPixelFormat(*hDC, nPixelFormat, &pfd), "Unable to set pixel format.");
	
	core::engine::gameEngine::error((hGLrc = wglCreateContext(*hDC)), "Unable to create 2.1 context");
	makeCurrent(*hDC);
	__debugMsg(OpenGL 1.x context creation);
}

void renderEngine::makeNewContext(){
	core::engine::gameEngine::error(hGLrc != 0, "1.1 context required to create 3.1 context.");
	int gla[] = {	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					WGL_CONTEXT_FLAGS_ARB, 0,
					0
	};
	HGLRC tempHGLRC = wglCreateContextAttribsARB(*hDC, 0, gla);
	if(!tempHGLRC)
		core::engine::gameEngine::error("Could not upgrade context");

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hGLrc);
	wglMakeCurrent(*hDC, tempHGLRC);
	hGLrc = tempHGLRC;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	__debugMsg(OpenGL 3.1 context creation);
}

void renderEngine::loadExtensions(){
	__debugMsg(Begin extension loading);
	core::engine::gameEngine::error(hGLrc, "1.1 context required to load extensions");
	__debugVal(hDC, *hDC);
	
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
	const char* extensions = wglGetExtensionsStringARB(*hDC);
	__debugMsg(Supported extension strings fetched);
	if(!strstr(extensions, "WGL_ARB_create_context"))
		core::engine::gameEngine::error("OpenGL 3/4 not supported.");
	__debugMsg(Checking OpenGL 3+ capability);
	__loadGL(wglCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC);
	__loadGL(glGenBuffers, PFNGLGENBUFFERSPROC);
	__loadGL(glBindBuffer, PFNGLBINDBUFFERPROC);
	__loadGL(glBufferData, PFNGLBUFFERDATAPROC);
	__loadGL(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
	__loadGL(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
	__loadGL(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC);
	__loadGL(glCreateShader, PFNGLCREATESHADERPROC);
	__loadGL(glShaderSource, PFNGLSHADERSOURCEPROC);
	__loadGL(glCompileShader, PFNGLCOMPILESHADERPROC);
	__loadGL(glGetShaderiv, PFNGLGETSHADERIVPROC);
	__loadGL(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
	__loadGL(glCreateProgram, PFNGLCREATEPROGRAMPROC);
	__loadGL(glAttachShader, PFNGLATTACHSHADERPROC);
	__loadGL(glLinkProgram, PFNGLLINKPROGRAMPROC);
	__loadGL(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
	__loadGL(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
	__loadGL(glDeleteShader, PFNGLDELETESHADERPROC);
	__loadGL(glUseProgram, PFNGLUSEPROGRAMPROC);
	__loadGL(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
	__loadGL(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
	__debugMsg(OpenGL extension loading);
}

void renderEngine::makeCurrent(HDC hDC, bool erase){
	if(!erase){
		wglMakeCurrent(hDC, hGLrc);
		return;
	}
	
	if(hGLrc){
		wglDeleteContext(hGLrc);
		hGLrc = NULL;
	}
	wglMakeCurrent(NULL, NULL);
}

void renderEngine::setup(){
	funcload = false;
	context = false;
	hGLrc = NULL;
	makeOldContext();
	loadExtensions();
	makeNewContext();
	
	view = glm::lookAt(glm::vec3(4,3,3), //Camera position
						glm::vec3(0,0,0), //Look at position
						glm::vec3(0,-1,0));
						
	projection = glm::perspective(core::settings::fov, core::settings::aspectRatio, 0.1f, 100.f);
	setupVertexAttributeArray();
	setupProgram();
}

void renderEngine::setupVertexAttributeArray(){
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

void renderEngine::setupProgram(){
	auto glProgram = glCreateProgram();
	glAttachShader(glProgram, loadShader("resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER));
	glAttachShader(glProgram, loadShader("resources/shaders/vertex.glsl", GL_VERTEX_SHADER));
	glLinkProgram(glProgram);
	
	GLint programResult = GL_TRUE;
	glGetProgramiv(glProgram, GL_LINK_STATUS, &programResult);
	
	if(programResult != GL_TRUE){
		std::size_t logLength;
		glGetProgramiv(glProgram, GL_INFO_LOG_LENGTH, (int*)&logLength);
		char* logContents = (char*)malloc(logLength);
		glGetProgramInfoLog(glProgram, logLength, (int*)&logLength, logContents);
		logContents[logLength-1] = 0;
		std::string msg = "Main OpenGL program could not link:\n" + std::string(logContents);
		free(logContents);
		core::engine::gameEngine::error(msg);
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glDisable(GL_DEPTH_TEST);
}

void renderEngine::setupVertexBuffer(){
	std::size_t memOffset = 0;
	
	for(auto &model : models){
		model->gpuOffset = memOffset;
		std::size_t memOverflowCheck = memOffset;
		if(memOverflowCheck < (memOffset += model->dataSize * sizeof(glm::vec3)))
			core::engine::gameEngine::error("Buffer overflow.\nGraphics.cpp LN" + __LINE__);
	};
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, memOffset, NULL, GL_STATIC_DRAW);
}

GLuint renderEngine::loadShader(std::string spathparam, GLenum shaderType){
	const GLuint shaderID = glCreateShader(shaderType);
	std::string shaderSource;
	std::ifstream shaderFile(spathparam, std::ios::in | std::ios::binary);
	
	if(!shaderFile.is_open())
		core::engine::gameEngine::error("File I/O error for shader at path: " + spathparam);
		
	shaderFile.seekg(0,std::ios_base::end);
	int shaderFileSize = shaderFile.tellg();
	shaderFile.seekg(0,std::ios_base::beg);
	
	char* shaderString = (char*) malloc(shaderFileSize+1);
	shaderFile.read(shaderString, shaderFileSize);
	shaderString[shaderFileSize] = '\0';
	
	glShaderSource(shaderID, 1, (const char**)&shaderString, NULL);
	glCompileShader(shaderID);
	
	GLint compResult = GL_TRUE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compResult);
	
	if(compResult == GL_FALSE){
		std::cout << "Fsize: " << shaderFileSize << std::endl << shaderString[shaderFileSize-4] << std::endl;
		std::cout << shaderString << std::endl;
		std::size_t shaderLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, (int*)&shaderLogLength);
		
		char* logContents = (char*) malloc(shaderLogLength);
		glGetShaderInfoLog(shaderID, shaderLogLength, (int*)&shaderLogLength, logContents);
		logContents[shaderLogLength-1] = 0;
		std::string errormsg = "Shader at path: " + spathparam + " could not compile. \n Error: \n\n" + logContents;
		free(logContents);
		core::engine::gameEngine::error(errormsg);
	}
	free(shaderString);
	return shaderID;
}
	
void graphics::engine::renderEngine::registerModel(model* tModel){
	tModel->cpuOffset = models.size();
	models.push_back(tModel);
}

std::size_t graphics::engine::renderEngine::lookupModel(std::string* uuidParam){
	return 0;
	bool found = false;
	std::size_t offset;
	for(offset =0; offset < models.size(); offset++){
//		if(models[offset]->uuid.equal(*uuidParam)){		//TODO: Will not work. c_str and what not
			found = true;
			break;
//		}
	}
	if(!found)
		core::engine::gameEngine::error(std::string("Search for nonloaded model with uuid: ") + *uuidParam);
	
	return offset;
}

graphics::model::model(GLuint texIDParam, std::vector<gpuVector>* data){
	texID = texIDParam;
	if(vertices->size() != UVs->size() != norms->size())
		core::engine::gameEngine::error("Error loading models -- size of vertices std::vector mismatch: Error in graphics.cpp LN " + __LINE__);
	
	dataSize = vertices->size() * sizeof(glm::vec3);
}

float graphics::normalizeX(short int x){return 0.f;};
float graphics::normalizeY(short int x){return 0.f;};

// Static reservations

HWND windowEngine::hWnd;
HDC windowEngine::hDC;
bool renderEngine::funcload;
bool renderEngine::context;
HGLRC renderEngine::hGLrc;

GLuint renderEngine::vertexArrayID;
GLuint renderEngine::vertexBufferID;
std::vector<graphics::model*> renderEngine::models;
glm::mat4 renderEngine::view;
glm::mat4 renderEngine::projection;
