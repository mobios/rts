#ifndef cpp_rts_graphics
#define cpp_rts_graphics
#include <windows.h>
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#include <cstdlib>
#include <string>
#include <fstream>

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094

namespace graphics{
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
			
			static void makeOldContext();
			static void makeNewContext();
			static void loadExtensions();
			static void makeCurrent(const HDC, const bool erase = false);
			static void setup();
			
			static GLuint loadShader(std::string, GLenum);
			static GLuint registerTexture(std::string, std::size_t, void*);
			static void setupProgram();
			static registerModel(model*);
		private:
			static std::vector<model> models;
		};
		
		struct settings{
			float aspcx;
			float aspcy;
		};
	}
	
	struct model{
		std::string texUuid;
		GLuint texID;
		GLuint modelID;
		model(float*);
		~model();
	}
	
	float normalizeX(short int);
	float normalizeY(short int);
}

#endif