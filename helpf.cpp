#include"SDL_image.h"
#include"SDL_ttf.h"
#include<iostream>
#include <sstream>
using namespace std;


SDL_Surface *load_image(string filename)
{
   	SDL_Surface* loaded_img = nullptr;
   	SDL_Surface* opt_img    = nullptr;
	
	cout << "load_img will attempt to load an image\n";
   	loaded_img= IMG_Load(filename.c_str());
	
	cout << "image loaded will start optimisation: load_image\n";

   	if( loaded_img )
   	{
    	cout << "starting optimisation: load_image\n";
		opt_img = SDL_DisplayFormat (loaded_img);
		cout << "got optimised img: load_image\n";
    	SDL_FreeSurface( loaded_img);
   	}
   	cout << filename << " from load image\n";
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

string formatted(int time)
{
    stringstream convert;
    string aux;
    string output="";
    
    int hundreds=0;
    int seconds=0;
    int minuites=0;
    int hours=0;

    hundreds = (time     / 10);
    seconds =  (hundreds / 100);
    minuites = (seconds  / 60);
    hours    = (minuites / 60);

    convert << hours%60 << " " << minuites%60 << " " << seconds%60 << " " << hundreds%100 ; //load numbers in the converter sstream;
    convert >> aux; // get hours
    output   += aux +":";
    aux       = "";
    convert >> aux; //get minuites
    if(minuites%60>=10) output  += aux+":";
    else            output  += "0"+aux+":";
    aux      = "";
    convert >> aux; //get seconds
    if(seconds%60>=10) output  += aux+".";
    else        output  += "0"+aux+".";
    aux      = "";
    convert >> aux; //get hundreds
    if(hundreds%100 < 10) output +="0"+aux;
    else                  output += aux;

    return output;
}
