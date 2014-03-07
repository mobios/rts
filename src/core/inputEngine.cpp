#include "inputEngine.h"

using namespace core::input;

MSG inputEngine::postMsg(MSG msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_LBUTTONDOWN:
		for(clickable* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->down_l();
				return 0;
			}
		}
		return msg;
		
	case WM_LBUTTONUP:
		for(clickable* mouseObj : mouseEvents){
			if(mouseObj->inbounds(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
				mouseObj->up_l();
				return 0;
			}
		}
		return msg;
		
	case 