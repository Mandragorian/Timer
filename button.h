#include"SDL.h"
#include<string>

#pragma once

class Button {
   
    private:
    //The attributes of the button
    SDL_Rect box;
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    SDL_Rect  clips[4];
    //the sprite sheet
    SDL_Surface* buttonSheet;

    void (*mouse_down)();
    void (*mouse_up)();
    void (*mouse_over)();   
    void (*mouse_out)(); 
    public:
    //Initialize the variables
    Button(int x, int y, int w, int h,std::string img,void (*down)(),void (*up)(),void (*over)(),void (*out)());
                       
    //Handles events and set the button's sprite region
    void handle_events(SDL_Event event);
                            
    //Shows the button on the screen
    void show(SDL_Surface* screen);
    
};
