SDLf=sdl-config --cflags --libs
CC=g++ -std=c++0x

timer : main.o helpf.o timer.o button.o
	$(CC)  -o timer main.o timer.o button.o  helpf.o `$(SDLf)` -lSDL_image -lSDL_ttf -I. 

main.o : main.cpp   
	$(CC)  -c main.cpp `$(SDLf)` -lSDL_image -lSDL_ttf -I.

helpf.o : helpf.cpp 
	$(CC)  -c helpf.cpp `$(SDLf)` -lSDL_image -lSDL_ttf -I.

timer.o : timer.cpp 
	$(CC)  -c timer.cpp `$(SDLf)` -lSDL_image -lSDL_ttf -I.

button.o : button.cpp
	$(CC)  -c button.cpp `$(SDLf)` -lSDL_image -lSDL_ttf -I.

main.o : helpf.h timer.h button.h
