#include<string>
#include"SDL.h"

SDL_Surface *load_image(std::string);

void apply_surface(SDL_Surface*, SDL_Surface*,int x=0 ,int y=0 ,SDL_Rect* clip=nullptr);

SDL_Rect set_clip(int,int,int,int);
