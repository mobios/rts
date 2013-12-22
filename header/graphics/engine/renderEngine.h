#ifndef cpp_rts_renderengine
#define cpp_rts_renderengine


namespace graphics{
	namespace engine{
		struct renderEngine{
			static bool funcLoad = false;
			static bool context = false;
			static const HDC* const hDC = &windowEngine::hDC;
			
			static HGLRC hGLrc = NULL;
			
			static void makeOldContext();
			static void makeNewContext();
			static void loadExtentions();
			static void registerShader();
			static void makeCurrent(const HDC, const bool erase = false);
			
#endif