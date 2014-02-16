#include "graphics/engine/windowEngine"
#include "core/common/global.h"
#include 

namespace graphics{
	namespace engine{
	
		static WNDCLASS* windowEngine::genWndClass(const HINSTANCE hInstance,
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
		
		static bool windowEngine::bindWndClass(WNDCLASS* WndClass){
			WNDCLASS wc = *WndClass;
			delete WndClass;
			WndClass = NULL;
			return RegisterClass(&wc);
		}
		
		static bool windowEngine::createWindow(HINSTANCE hInstance, WNDPROC wndProc){
			error(bindWndClass(genWndClass(hInstance, wndProc, $apptitle)), 
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
								 
			error(hWnd, "Unable to create window.");
			
			hDC = GetDC(hWnd);
			error(hDC, "Unable to fetch device context.");
			makeAvailable();
		}
		
		static void makeAvailable(){
			ShowWindow(hWnd, SW_SHOW);
			SetForegroundWindow(hWnd);
			SetFocus(hWnd);
		}
		
			
		