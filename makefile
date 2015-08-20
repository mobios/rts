# all: rts.exe
# x86_64-w64-mingw32-g++ -mwindows src\engine.o object/graphics.o object/input.o object/loader.o object/util.o -o rts.exe -lstdc++ -lgdi32 -lopengl32 -static -ggdb -mwindows
# rts.exe: object/engine.o object/graphics.o object/input.o object/loader.o object/util.o
	# x86_64-w64-mingw32-g++ -mwindows object/engine.o object/graphics.o object/input.o object/loader.o object/util.o -o rts.exe -lstdc++ -lgdi32 -lopengl32 -static -ggdb -mwindows
	
# object/engine.o: header/core/gameEngine.h src/core/gameEngine.cpp
	# g++ -Iheader -c -std=c++0x src/core/gameEngine.cpp -o object/engine.o -g
	
# object/input.o: header/core/inputEngine.h src/core/inputEngine.cpp
	# g++ -Iheader -c -std=c++0x src/core/inputEngine.cpp -o object/input.o -g
	
# object/graphics.o: header/graphics/glWrapper.h header/graphics/graphics.h src/graphics/graphics.cpp
	# g++ -Iheader -c -std=c++0x src/graphics/graphics.cpp -o object/graphics.o -g

# object/loader.o: header/graphics/graphics.h header/graphics/objectLoader.h src/graphics/objectLoader.cpp
	# g++ -Iheader -c -std=c++0x src/graphics/objectLoader.cpp -o object/loader.o -g

# object/util.o: header/utils/util.h src/utils/util.cpp
	# g++ -Iheader -c -std=c++0x src/utils/util.cpp -o object/util.o -g
	
	
target := rts.exe
lflags := -mwindows -static -lgdi32 -lopengl32
cflags := -std=c++0x -g -Iheader -m32
cc := C:\MinGW\bin\g++

srcfiles := $(wildcard */*/*.cpp)
hdrfiles := $(wildcard */*/*.h)

objfiles := $(srcfiles:.cpp=.o)
dependencies := $(srcfiles:.cpp=.d)

build: $(target)

$(target): $(objfiles)
	$(cc) -o $(target) $(objfiles) $(lflags)
	
.cpp.o:
	$(cc) $(cflags) -MMD -MP -c $< -o $@

	
-include $(dependencies)