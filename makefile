all: rts.exe

rts.exe: object/main.o
	g++ object/main.o -lopengl32 -lgdi32 -orts.exe -static
	
object/main.o: header/main.h source/main.cpp
	g++ -Iheader -c -std=c++0x source/main.cpp
	mv main.o object