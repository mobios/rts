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
			
			static void makeOldContext();
			static void makeNewContext();
			static void loadExtensions();
			static void makeCurrent(const HDC, const bool erase = false);
			
			static void swapBuffers(){SwapBuffers(*hDC);};
			
			static void setup();
			static void setupVertexAttributeArray();
			static void setupProgram();
			static void setupVertexBuffer();
			static void populateVertexBuffer();
			
			static GLuint loadShader(std::string, GLenum);
			static GLuint registerTexture(std::string, std::size_t, void*);
			static void registerModel(model);
			static std::size_t lookupModel(const char*);
			static void renderModel(std::size_t, glm::mat4*);
			
			static const glm::mat4 getViewMatrix(){return view;};
			static const glm::mat4 getProjectionMatrix(){return projection;};
						
			class uniformHandles{
				friend struct renderEngine;
				static GLuint textureSampler;
				static GLuint MVPmatrix;
			public:
				static GLuint getTextureSampler(){return textureSampler;};
				static GLuint getMVPmatrix(){return MVPmatrix;};
			};
			
		private:
			static std::vector<model> models;
			static GLuint programID;
			
			static GLuint vertexArrayID;
			static GLuint vertexBufferID;
			
			static glm::mat4 view;
			static glm::mat4 projection;
		};
	}
	
	struct model{
		std::string uuid;
		GLuint texID;
		GLuint gpuOffset;
		std::size_t cpuOffset;
		std::size_t dataSize;
		
		std::vector<graphics::gpuVertex> getData(){return data;};
		void releaseData(){data.clear();};
		
		void render(glm::mat4*);
		
		model(GLuint, std::vector<graphics::gpuVertex>);
		std::vector<graphics::gpuVertex> data;
	};
	
	struct gpuVertex{
		glm::vec3 vertex;
		glm::vec2 uv;
		glm::vec3 normal;
	};
	
	float normalizeX(short int);
	float normalizeY(short int);
}

extern std::ostream& operator<<(std::ostream& os, const graphics::gpuVertex& gV);
#endif