all: rts.exe

rts.exe: object/engine.o object/graphics.o object/input.o
	g++ object/engine.o object/graphics.o object/input.o -lopengl32 -lgdi32 -orts.exe -static -mwindows
	
object/engine.o: header/core/gameEngine.h src/core/gameEngine.cpp
	g++ -Iheader -c -std=c++0x src/core/gameEngine.cpp -o engine.o
	mv engine.o object
	
object/input.o: header/core/inputEngine.h src/core/inputEngine.cpp
	g++ -Iheader -c -std=c++0x src/core/inputEngine.cpp -o object/input.o
	
object/graphics.o: header/graphics/glWrapper.h header/graphics/graphics.h src/graphics/graphics.cpp
	g++ -Iheader -c -std=c++0x src/graphics/graphics.cpp
	mv graphics.o object