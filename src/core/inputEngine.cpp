#include "inputEngine.h"

using namespace core::input;
void inputEngine::checkModify(WPARAM wParam){
	if(wParam | MK_SHIFT)
		shift = true;
	else
		shift = false;
		
	if(wParam | MK_CTRL)
		ctrl = true;
	else
		ctrl = false;
}
	
MSG inputEngine::postMsg(MSG msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_LBUTTONDOWN:
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				checkModify(wParam);					
				mouseObj->down_l();
				return 0;
			}
		}
		return msg;
		
	case WM_LBUTTONUP:
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				checkModify(wParam);
				mouseObj->up_l();
				return 0;
			}
		}
		return msg;
		
	case WM_RBUTTONDOWN:
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				checkModify(wParam);
				mouseObj->down_r();
				return 0;
			}
		}
		return msg;	
		
	case WM_RBUTTONUP:
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				checkModify(wParam);
				mouseObj->up_r();
				return 0;
			}
		}
		return msg;
		
	case WM_MOUSEMOVE:
		if(settings::raw || !settings::hwpointer)
			return msg;
		
		mousex = GET_X_LPARAM(lparam);
		mousey = GET_Y_LPARAM(lparam);
		return 0;
	}
	return msg;
}
	