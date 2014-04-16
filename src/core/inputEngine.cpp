#include "inputEngine.h"

using namespace core::input;

bool flatMouse::inbounds(signed short x, signed short y){
	testx = graphics::normalizeX(x);
	testy = graphics::normalizeY(y);
	
	if(testx > x+xsize || testx < x)
		return false;
	
	if(testy > y+ysize || testy < y)
		return false;
		
	return true;
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

void inputEngine::registerMouse(flatMouse* mobj){
	mouseEvents.push(mobj);
}

void inputEngine::registerKey(keyObj* kobj){
	keyEvents.push(kobj);
}

void inputEngine::notifyDead(flatMouse* mobj){
	mouseEvents.remove(mobj);
}

void inputEngine::removeKey(keyObj* kobj){
	keyEvents.remove(kobj);
}

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

std::list<flatMouse*> inputEngine::mouseEvents;
std::list<keyObj*> inputEngine::keyEvents;
bool inputEngine::shift;
bool inputEngine::ctrl;
int inputEngine::mousex;
int inputEngine::mousey;
bool settings::raw;
bool settings::hwpointer;