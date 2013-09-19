#include"SDL.h"
#include<string>
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<iostream>
#include <sstream>
using namespace std;


SDL_Surface *load_image(string filename)
{
   SDL_Surface* loaded_img = nullptr;
   SDL_Surface* opt_img    = nullptr;

   loaded_img= IMG_Load(filename.c_str());

   if( loaded_img )
   {
       opt_img = SDL_DisplayFormat (loaded_img);
       SDL_FreeSurface( loaded_img);
   }

   return opt_img;

}


void apply_surface(SDL_Surface* source, SDL_Surface* destination,int x=0,int y=0, SDL_Rect* clip = nullptr)
{
    SDL_Rect offset;

    offset.x=x;
    offset.y=y;

    SDL_BlitSurface(source, clip,destination, &offset);
}


SDL_Rect set_clip(int x,int y, int w, int h)
{
    SDL_Rect aux;

    aux.x=x;
    aux.y=y;
    aux.w=w;
    aux.h=h;

    return aux;
}
