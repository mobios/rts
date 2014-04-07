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
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){					
				mouseObj->down_l();
				return 0;
			}
		}
		return msg;
		
	case WM_LBUTTONUP:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->up_l();
				return 0;
			}
		}
		return msg;
		
	case WM_RBUTTONDOWN:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->down_r();
				return 0;
			}
		}
		return msg;	
		
	case WM_RBUTTONUP:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->up_r();
				return 0;
			}
		}
		return msg;
		
	case WM_MOUSEMOVE:
		checkModify(wParam);
		if(settings::raw)
			return msg;
		
		if(highlight != NULL && !highlight->inbounds(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam))
			highlight->out();
		
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)){
				highlight = mouseObj;
				highlight.over();
				return 0;
			}
		}
		
		if(!settings::hwpointer)
			return 0;
		
		mousex = GET_X_LPARAM(lparam);
		mousey = GET_Y_LPARAM(lparam);
		return 0;
	}
	return msg;
}


	