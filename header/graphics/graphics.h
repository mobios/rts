
namespace graphics{
	namespace engine{
		struct windowEngine{
			static HWND hWnd;
			static HDC hDC;
			
			static WNDCLASS* genWndClass(const HINSTANCE, const WNDPORC, const LPCSTR) const;
			static bool bindWndClass(WNDCLASS*);
			static bool createWindow(const HINSTANCE, const WNDPROC);
			static void makeAvailable();
			static HDC getHDC();
			static HWND getHWND();
		}
		
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
		}
	}
}
