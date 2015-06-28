#ifndef cpp_rts_all_inc
#define cpp_rts_all_inc

#include "macro.h"

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


typedef void (*TRIGGER)();
typedef void (*mouseMovementMessage)(float, float);


#endif