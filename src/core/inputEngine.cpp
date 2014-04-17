#include "core/inputEngine.h"
#include "graphics/graphics.h"

using namespace core::input;

bool flatMouse::inbounds(signed short x, signed short y){
	auto testx = graphics::normalizeX(x);
	auto testy = graphics::normalizeY(y);
	
	if(testx > x+xsize || testx < x)
		return false;
	
	if(testy > y+ysize || testy < y)
		return false;
		
	return true;
}

bool core::inputEngine::postMsg(UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_LBUTTONDOWN:
		std::cout << "Lclick\n";
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){					
				mouseObj->down_l();
				return true;
			}
		}
		return false;
		
	case WM_LBUTTONUP:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->up_l();
				return true;
			}
		}
		return false;
		
	case WM_RBUTTONDOWN:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->down_r();
				return true;
			}
		}
		return false;	
		
	case WM_RBUTTONUP:
		checkModify(wParam);
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->up_r();
				return true;
			}
		}
		return false;
		
	case WM_MOUSEMOVE:
		std::cout << "X: " << GET_X_LPARAM(lParam) << "  Y: " << GET_Y_LPARAM(lParam) << std::endl;
		checkModify(wParam);
		if(settings::getRaw())
			return false;
		
		if(highlight != NULL && !highlight->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
			highlight->out();
		
		for(flatMouse* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				highlight = mouseObj;
				highlight->over();
				return true;
			}
		}
		
		if(settings::getHwpointer())
			return true;
		
		mousex = GET_X_LPARAM(lParam);
		mousey = GET_Y_LPARAM(lParam);
		return true;
	}
	return false;
}

void core::inputEngine::registerMouse(flatMouse* mobj){
	mouseEvents.push_back(mobj);
}

void core::inputEngine::registerKey(keyObj* kobj){
	keyEvents.push_back(kobj);
}

void core::inputEngine::notifyDead(flatMouse* mobj){
	mouseEvents.remove(mobj);
}

void core::inputEngine::removeKey(keyObj* kobj){
	keyEvents.remove(kobj);
}

void core::inputEngine::checkModify(WPARAM wParam){
	if(wParam | MK_SHIFT)
		shift = true;
	else
		shift = false;
		
	if(wParam | MK_CONTROL)
		ctrl = true;
	else
		ctrl = false;
}



std::list<flatMouse*> core::inputEngine::mouseEvents;
std::list<keyObj*> core::inputEngine::keyEvents;
bool core::inputEngine::shift;
bool core::inputEngine::ctrl;
int core::inputEngine::mousex;
int core::inputEngine::mousey;
bool settings::raw;
bool settings::hwpointer;