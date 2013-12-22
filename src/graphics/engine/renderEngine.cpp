#include "graphics/renderEngine.h"
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>

namespace graphics{
	namespace engine{
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
			error(nPixelFormat, "Unable to choose pixel format.");
			
			error(SetPixelFormat(*hDC, nPixelFormat, &pfd), "Unable to set pixel format.");
			
			error((hGLrc = wglCreateContext(*hDC)), "Unable to create 2.1 context");
			makeCurrent(hDC);
		}
		
		void renderEngine::makeNewContext(){
			error(hGLrc, "1.1 context required to create 3.1 context.");
			
			