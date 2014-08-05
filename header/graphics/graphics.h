#ifndef cpp_rts_graphics
#define cpp_rts_graphics

#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GL\gl.h>
#include <windows.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094

namespace graphics{
	struct model;
	struct gpuVertex;
	
	namespace engine{
		struct windowEngine{
			static HWND hWnd;
			static HDC hDC;
			
			static WNDCLASS* genWndClass(const HINSTANCE, const WNDPROC, const LPCSTR);
			static bool bindWndClass(WNDCLASS*);
			static bool createWindow(const HINSTANCE, const WNDPROC);
			static void makeAvailable();
			static HDC getHDC();
			static HWND getHWND();
			static void setup(const HINSTANCE, const WNDPROC);
		};
		
		struct renderEngine{
			static bool funcload;
			static bool context;
			static constexpr HDC* hDC = &windowEngine::hDC;
			static HGLRC hGLrc;
			
			static GLuint vertexArrayID;
			static GLuint vertexBufferID;
			
			static glm::mat4 view;
			static glm::mat4 projection;
			
			static void makeOldContext();
			static void makeNewContext();
			static void loadExtensions();
			static void makeCurrent(const HDC, const bool erase = false);
			
			static void setup();
			static void setupVertexAttributeArray();
			static void setupProgram();
			static void setupVertexBuffer();
			static void finalizeRenderEngine();
			
			static GLuint loadShader(std::string, GLenum);
			static GLuint registerTexture(std::string, std::size_t, void*);
			static void registerModel(model*);
			static std::size_t lookupModel(std::string*);
			
		private:
			static std::vector<model*> models;
		};
	}
	
	struct model{
		std::string uuid;
		GLuint texID;
		GLuint gpuOffset;
		std::size_t cpuOffset;
		std::size_t dataSize;
		model(GLuint, std::vector<gpuVertex>*);
		~model();
	};
	
	struct gpuVertex{
		glm::vec3 vertex;
		glm::vec2 uv;
		glm::vec3 normal;
	};
	
	float normalizeX(short int);
	float normalizeY(short int);
}

#endif