#ifndef cpp_rts_graphics
#define cpp_rts_graphics

#include "all.h"
#include "core/error.h"
#include "util/loader.h"
#include "core/settings.h"

namespace graphics
{
	struct model;
	struct gpuVertex;

	enum programType
	{
		PRG_UI,
		PRG_MODEL
	};

	
	namespace engine
	{
		struct windowEngine
		{
			static HWND hWnd;
			static HDC hDC;
			
			static WNDCLASS* genWndClass(const HINSTANCE, const WNDPROC, const LPCSTR);
			static bool bindWndClass(WNDCLASS*);
			static bool createWindow(const HINSTANCE, const WNDPROC);
			static void makeAvailable();
			static HDC getHDC();
			static HWND getHWND(){return hWnd;};
			static void setup(const HINSTANCE, const WNDPROC);
		};
		
		struct renderEngine
		{

			static GLuint currentTextureVector;

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
			static void setupPrograms();
			static void setupVertexBuffer();
			static void populateVertexBuffer();
			
			static GLuint initializeProgram(const char *, const char *);
			static void assertProgram(programType);

			static GLuint loadShader(std::string, GLenum);
			static GLuint registerTexture(std::string, std::size_t, void*);
			static void registerModel(model*);
			static std::size_t lookupModel(const char*);
			static void renderModel(std::size_t, glm::mat4*);

			static void renderText();
			
			static const glm::mat4 getViewMatrix(){return view;};
			static const glm::mat4 getProjectionMatrix(){return projection;};
			
			static void setViewMatrix(glm::mat4* vParam){view = *vParam;};
			
			class uniformHandles
			{
				friend struct renderEngine;
				static GLuint textureSampler;
				static GLuint MVPmatrix;
			public:
				static GLuint getTextureSampler(){return textureSampler;};
				static GLuint getMVPmatrix(){return MVPmatrix;};
			};
			
		private:
			static std::vector<model*> models;
			
			static GLuint vertexArrayID;
			static GLuint vertexBufferID;
			
			static glm::mat4 view;
			static glm::mat4 projection;

			static GLuint currentProgram;
			static GLuint modelProgramID;
			static GLuint GUIProgramID;
		};
	}
	
	struct model
	{
		std::string uuid;
		GLuint texID;
		long long gpuBufferOffset;
		std::size_t vectorOffset;
		std::size_t indices;
		std::size_t bytes;
		
		std::vector<graphics::gpuVertex> getData(){return data;};
		void releaseData(){data.clear();};
		
		void render(glm::mat4*);
		
		model(GLuint, std::vector<graphics::gpuVertex>);
		std::vector<graphics::gpuVertex> data;
	};
	
	struct gpuVertex
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		glm::vec3 normal;
	};
	
	float normalizeX(short int);
	float normalizeY(short int);
}

extern std::ostream& operator<<(std::ostream& os, const graphics::gpuVertex& gV);
#endif