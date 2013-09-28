SDLf = sdl-config --cflags --libs
CC   = g++ -std=c++0x
OBJ  = main.o helpf.o timer.o button.o


timer : $(OBJ)
	$(CC) -o timer $^ `$(SDLf)` -lSDL_image -lSDL_ttf -I.

%.o : %.cpp 
	$(CC) -c $< `$(SDLf)` -lSDL_image -lSDL_ttf -I.


