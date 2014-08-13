all: rts.exe

rts.exe: object/engine.o object/graphics.o object/input.o object/loader.o object/util.o
	g++ object/engine.o object/graphics.o object/input.o object/loader.o object/util.o -lopengl32 -lgdi32 -orts.exe -static -mwindows -g
	
object/engine.o: header/core/gameEngine.h src/core/gameEngine.cpp
	g++ -Iheader -c -std=c++0x src/core/gameEngine.cpp -o object/engine.o -g
	
object/input.o: header/core/inputEngine.h src/core/inputEngine.cpp
	g++ -Iheader -c -std=c++0x src/core/inputEngine.cpp -o object/input.o -g
	
object/graphics.o: header/graphics/glWrapper.h header/graphics/graphics.h src/graphics/graphics.cpp
	g++ -Iheader -c -std=c++0x src/graphics/graphics.cpp -o object/graphics.o -g

object/loader.o: header/graphics/graphics.h header/graphics/objectLoader.h src/graphics/objectLoader.cpp
	g++ -Iheader -c -std=c++0x src/graphics/objectLoader.cpp -o object/loader.o -g

object/util.o: header/utils/util.h src/utils/util.cpp
	g++ -Iheader -c -std=c++0x src/utils/util.cpp -o object/util.o -g