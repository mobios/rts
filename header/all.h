#ifndef cpp_rts_all_inc
#define cpp_rts_all_inc

#define GLM_FORCE_RADIANS
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094

#define PARAM_DEBUG

#define __loadGL(func, ptrtype) func = (ptrtype) wglGetProcAddress(#func)

#undef __STRICT_ANSI__
	#include <stdio.h>
	#include <cmath>
#define __STRICT_ANSI__

#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <io.h>
#include <fcntl.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <windows.h>
#include <windowsx.h>
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>


#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "global.h"

#include "util.h"
#include "graphics.h"
#include "gameEngine.h"
#include "objectLoader.h"
#include "inputEngine.h"
#include "font.h"

#endif