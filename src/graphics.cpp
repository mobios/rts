#include "all.h"
#include "glWrapper.h"

using namespace graphics::engine;

void windowEngine::setup(const HINSTANCE hInst, const WNDPROC WndProc){
	createWindow(hInst, WndProc);
	__debugMsg(Window creation);
}

WNDCLASS* windowEngine::genWndClass(const HINSTANCE hInstance,
										   const WNDPROC WndProc,
										   const LPCSTR className)
{
										   
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
		  
	hWnd = CreateWindow($apptitle,
						$apptitle,
						WS_POPUP,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						800,
						600,
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
	
	glViewport(0,0,800,600);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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
	__loadGL(glBufferSubData, PFNGLBUFFERSUBDATAPROC);
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
	__loadGL(glActiveTexture, PFNGLACTIVETEXTUREPROC);
	__loadGL(glUniform1i, PFNGLUNIFORM1IPROC);
	__loadGL(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
	__loadGL(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
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
						glm::vec3(0,1,0));
						
	projection = glm::perspective(core::settings::fov, core::settings::aspectRatio, 0.1f, 100.f);
	setupVertexAttributeArray();
	setupProgram();
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	objectLoader::setup();
}

void renderEngine::setupVertexAttributeArray(){
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

GLuint renderEngine::initializeProgram(const char* fragment_path, const char* vertex_path)
{
	GLuint return_program = glCreateProgram();
	glAttachShader(return_program, fragment_path, GL_FRAGMENT_SHADER);
	glAttachShader(return_program, vertex_path, GL_VERTEX_SHADER);
	glLinkProgram(return_program);

	GLint programResult = GL_TRUE;
	glGetProgramiv(programID, GL_LINK_STATUS, &programResult);
	
	if(programResult != GL_TRUE){
		std::size_t logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, (int*)&logLength);
		char* logContents = (char*)malloc(logLength);
		glGetProgramInfoLog(programID, logLength, (int*)&logLength, logContents);
		logContents[logLength-1] = 0;

		std::string msg = "Fragment Shader: " + std::string(fragment_path) + "\nVertex Shader: " + std::string(vertex_path) + "\n";

		msg += "OpenGL program could not link:\n" + std::string(logContents);
		free(logContents);
		core::engine::gameEngine::error(msg);
	}
	return return_program;
}

void renderEngine::setupProgram(){
	// programID = glCreateProgram();
	// glAttachShader(programID, loadShader("resources/shaders/modelf.glsl", GL_FRAGMENT_SHADER));
	// glAttachShader(programID, loadShader("resources/shaders/modelv.glsl", GL_VERTEX_SHADER));
	// glLinkProgram(programID);
	
	// GLint programResult = GL_TRUE;
	// glGetProgramiv(programID, GL_LINK_STATUS, &programResult);
	
	// if(programResult != GL_TRUE){
	// 	std::size_t logLength;
	// 	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, (int*)&logLength);
	// 	char* logContents = (char*)malloc(logLength);
	// 	glGetProgramInfoLog(programID, logLength, (int*)&logLength, logContents);
	// 	logContents[logLength-1] = 0;
	// 	std::string msg = "Main OpenGL program could not link:\n" + std::string(logContents);
	// 	free(logContents);
	// 	core::engine::gameEngine::error(msg);
	// }
	modelProgramID = initializeProgram("resources/shaders/modelf.glsl","resources/shaders/modelv.glsl");
	GUIProgramID = initializeProgram("resources/shaders/guif.glsl","resources/shaders/guiv.glsl");
	
	glUseProgram(programID);
	uniformHandles::MVPmatrix = glGetUniformLocation(programID, "MVP");
	uniformHandles::textureSampler = glGetUniformLocation(programID, "texSampler");
	glUniform1i(uniformHandles::textureSampler,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void renderEngine::setupVertexBuffer(){
	std::size_t gpuSize = 0;
	
	for(auto &model : models){
		model->gpuBufferOffset = gpuSize;
		gpuSize += model->bytes;
	};
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, gpuSize, &((models[0]->data)[0]), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,	
	                      3,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(graphics::gpuVertex),
						  (void*)0);
	glEnableVertexAttribArray(1);
						  
	glVertexAttribPointer(1,	
	                      2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(graphics::gpuVertex),
						  (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
						  
	glVertexAttribPointer(2,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(graphics::gpuVertex),
						  (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));
}

void renderEngine::populateVertexBuffer(){
	std::size_t offset = 0;
	for(auto &model : models){
		glBufferSubData(GL_ARRAY_BUFFER, model->gpuBufferOffset, model->indices, &((model->data)[0]));
	}
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
	tModel->vectorOffset = models.size();
	models.push_back(tModel);
}

void graphics::engine::renderEngine::renderModel(std::size_t offset, glm::mat4* matrix){
	if(offset >= models.size())
		core::engine::gameEngine::error("Tried finding model at postition " + util::itos(offset) + "\nOnly " + util::itos(models.size()) + " models loaded");
	models[offset]->render(matrix);
}

std::size_t graphics::engine::renderEngine::lookupModel(const char* uuidParam){
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

void graphics::model::render(glm::mat4* modelPosition){
	glm::mat4 cpuMVP = renderEngine::getProjectionMatrix() * renderEngine::getViewMatrix() * (*modelPosition);
	glUniformMatrix4fv(renderEngine::uniformHandles::getMVPmatrix(), 1, GL_FALSE, &cpuMVP[0][0]);
	glDrawArrays(GL_TRIANGLES, gpuBufferOffset, indices);
}

graphics::model::model(GLuint texIDParam, std::vector<graphics::gpuVertex> dataParam){
	texID = texIDParam;

	indices = dataParam.size();
	bytes = dataParam.size() * sizeof(gpuVertex);
	
	data = dataParam;
}

std::ostream& operator<<(std::ostream& os, const graphics::gpuVertex &gV){
	os << "Vertex" << std::endl;
	os << "--x: " << gV.vertex.x << std::endl;
	os << "--y: " << gV.vertex.y << std::endl;
	os << "--z: " << gV.vertex.z << std::endl << std::endl;
	
	os << "UV" << std::endl;
	os << "--S" << gV.uv.x << std::endl;
	os << "--T" << gV.uv.y << std::endl << std::endl;
	
	os << "Normal" << std::endl;
	os << "--x: " << gV.normal.x << std::endl;
	os << "--y: " << gV.normal.y << std::endl;
	os << "--z: " << gV.normal.z << std::endl << std::endl;
}

float graphics::normalizeX(short int x){return 0.f;};
float graphics::normalizeY(short int x){return 0.f;};

// Static reservations

HWND windowEngine::hWnd;
HDC windowEngine::hDC;
bool renderEngine::funcload;
bool renderEngine::context;
HGLRC renderEngine::hGLrc;

GLuint renderEngine::uniformHandles::textureSampler;
GLuint renderEngine::uniformHandles::MVPmatrix;

GLuint renderEngine::programID;
GLuint renderEngine::vertexArrayID;
GLuint renderEngine::vertexBufferID;
std::vector<graphics::text> renderEngine::elements_text;
std::vector<graphics::model*> renderEngine::models;
glm::mat4 renderEngine::view;
glm::mat4 renderEngine::projection;
