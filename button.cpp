#include"SDL.h"
#include"SDL_image.h"
#include<string>
#include"helpf.h"
#include<iostream>

#pragma once

using namespace std;

void pass(){}

enum states {CLIP_MOUSEOVER, CLIP_MOUSEDOWN, CLIP_MOUSEOUT, CLIP_MOUSEUP};

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
    Button(int x, int y, int w, int h,string img,void (*down)(),void (*up)(),void (*over)(),void (*out)());
                       
    //Handles events and set the button's sprite region
    void handle_events(SDL_Event event);
                            
    //Shows the button on the screen
    void show(SDL_Surface* screen);
    
};

Button::Button(int x, int y, int w, int h,string img,void (*down)(),void (*up)(),void (*over)(),void (*out)())
{
    cout << "in button constr\n";

	box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
	
	cout <<"box initialised\n";

    clip =&clips[CLIP_MOUSEOUT];
	
	cout <<"clip array init\n";
	cout << img << "\n";
    buttonSheet= load_image(img);
    if(buttonSheet) cout << "yay!\n";
   


    if(down) mouse_down = down;
	else	 mouse_down = pass;
	if(up)   mouse_up   = up;
	else	 mouse_up   = pass;
    if(over) mouse_over = over;
	else	 mouse_over = pass;
    if(out)  mouse_out  = out;
	else	 mouse_out  = pass;

	clips[CLIP_MOUSEOUT].x=0;
	clips[CLIP_MOUSEOUT].y=0;
	clips[CLIP_MOUSEOUT].w=w;
	clips[CLIP_MOUSEOUT].h=h;

	clips[CLIP_MOUSEOVER].x=w;
	clips[CLIP_MOUSEOVER].y=0;
	clips[CLIP_MOUSEOVER].w=w;
	clips[CLIP_MOUSEOVER].h=h;

	clips[CLIP_MOUSEDOWN].x=0;
	clips[CLIP_MOUSEDOWN].y=h;
	clips[CLIP_MOUSEDOWN].w=w;
	clips[CLIP_MOUSEDOWN].h=h;

	clips[CLIP_MOUSEUP].x=w;
	clips[CLIP_MOUSEUP].y=h;
	clips[CLIP_MOUSEUP].w=w;
	clips[CLIP_MOUSEUP].h=h;

}

void Button::handle_events(SDL_Event event)
{
    int x =0;
    int y =0;

    if(event.type == SDL_MOUSEMOTION)
    {
        x = event.motion.x;
        y = event.motion.y;

        if((x>box.x) && (x < box.x +box.w) && (y > box.y)&&(y<box.y+box.h)) //mouseover
        {
            clip = &clips[CLIP_MOUSEOVER];
            mouse_over();
			//cout << "mouseover\n";
        }
        else //mouseout
        {
            clip=&clips[CLIP_MOUSEOUT];
			mouse_out();
			//cout << "mouseout\n";
        }
    }

    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            x = event.button.x;
            y = event.button.y;

           if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) //mousedown
            {
                clip=&clips[CLIP_MOUSEDOWN];
				mouse_down();
				//cout << "mousedown\n";
            }
        }
    }
    else
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) //mouseup
            {
                clip=&clips[CLIP_MOUSEUP];
				mouse_up();
				//cout <<"mouseup\n";
            }
        }
    }
}

void Button::show(SDL_Surface* screen)
{
    apply_surface(buttonSheet,screen,box.x,box.y,clip);
	//SDL_Flip(screen);
}

