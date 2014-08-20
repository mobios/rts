#include "core/inputEngine.h"
#include "graphics/graphics.h"
#include "core/gameEngine.h"

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

void core::inputEngine::setup(){
	input::settings::raw = false;
	input::settings::hwpointer = false;
	input::settings::captureMouse = true;
}

bool core::inputEngine::postMsg(UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_KEYDOWN:
		keys[(unsigned char)wParam] = true;
		return true;
		
	case WM_KEYUP:
		keys[(unsigned char)wParam] = false;
		return true;
		
	case WM_LBUTTONDOWN:;
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
		if(input::settings::captureMouse){
			input::settings::captureMouse = false;
			centerCursor();
		}
		else{
			input::settings::captureMouse = true;
		}
		
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
		if(moved){
			moved = false;
			return true;
		}
		checkModify(wParam);
		if(input::settings::getRaw())
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
		
		if(input::settings::getHwpointer())
			return true;
		
		mousex = GET_X_LPARAM(lParam);
		mousey = GET_Y_LPARAM(lParam);
		if(!input::settings::captureMouse){
			centerCursor();
			core::engine::gameEngine::moveAngles(float(300-mousey)/1000, float(mousex-400)/1000);
		}
		return true;
	
	case WM_DESTROY:
		std::cout << "WM_DESTROY posted...\nExiting\n";
		core::engine::gameEngine::teardown();
	
	case WM_CLOSE:
		std::cout << "WM_CLOSE posted...\nExiting\n";
		core::engine::gameEngine::teardown();
	}
	return false;
}

void core::inputEngine::registerMouse(flatMouse* mobj){
	mouseEvents.push_back(mobj);
}

bool core::inputEngine::queryKey(unsigned char keyQuery){
	return keys[keyQuery];
}

void core::inputEngine::notifyDead(flatMouse* mobj){
	mouseEvents.remove(mobj);
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

void core::inputEngine::centerCursor(){
	POINT cursor;
	cursor.x = 400;
	cursor.y = 300;
	ClientToScreen(graphics::engine::windowEngine::getHWND(),&cursor);
	SetCursorPos(cursor.x, cursor.y);
	moved = true;
}

std::list<flatMouse*> core::inputEngine::mouseEvents;
bool core::inputEngine::shift;
bool core::inputEngine::ctrl;
bool core::inputEngine::moved;
int core::inputEngine::mousex;
int core::inputEngine::mousey;
flatMouse* core::inputEngine::highlight;
bool core::inputEngine::keys[256];
bool settings::raw;
bool settings::hwpointer;
bool settings::captureMouse;