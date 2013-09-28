#include"SDL.h"
#include<string>
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<iostream>
#include <sstream>
#include"helpf.h"
#include"timer.h"
#include"button.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

enum myenum {CLIP_MOUSEOVER,CLIP_MOUSEOUT,CLIP_MOUSEDOWN,CLIP_MOUSEUP};

SDL_Event event;

SDL_Rect clip;

SDL_Surface* screen      = nullptr;
SDL_Surface* background = nullptr;

TTF_Font* font           = nullptr;

SDL_Color textColour     = {255,255,255};

SDL_Surface* load_image(string);
void apply_surface(SDL_Surface*, SDL_Surface*,int,int,SDL_Rect*);

Timer Clock;

bool init()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

    if(!screen) return false;

    if( TTF_Init() == -1) return false;
    
    SDL_WM_SetCaption("Time Tools", nullptr);

    font = TTF_OpenFont("Impact.ttf",20);

    background = load_image("back.png");

    return true;
    
}

void start_stop_timer()
{
	if(Clock.is_running()) Clock.stop();
	else Clock.start();
	//cout <<"start_stop called \n";
}
int main (int argc, char* args[])
{
    bool quit    = false;
    //bool running = false;
    
    

    //Timer clock;

    if(!init()) return 1;
   
    Button start_stop((SCREEN_WIDTH-100)/2,SCREEN_HEIGHT-160,100,80,(string)"start_stop_button.png",start_stop_timer,nullptr,nullptr,nullptr);//,nullptr,nullptr,nullptr);	

    while(!quit)
    {
        //start_stop.show(screen);
		
		while(SDL_PollEvent(&event))
        {
            start_stop.handle_events(event);
			
			if(event.type==SDL_QUIT) quit = true;
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_s)
                {
                    if(Clock.is_running())	
						Clock.stop();
                    else	
						Clock.start();
                         
                }
                else if(event.key.keysym.sym == SDLK_p)
                {
                    if(Clock.is_running())
                    	Clock.pause();
                    else
                    	Clock.resume();
                }
            }
                
        }
        if(Clock.is_running()) //get and display time
        {
            SDL_Surface* seconds=nullptr;
            string time="";

            time = formatted(Clock.get_ticks());
            
            apply_surface(background,screen,clip.x,clip.y,&clip);


            seconds = TTF_RenderText_Solid(font, time.c_str(),textColour);

            clip = set_clip(/*(SCREEN_WIDTH -seconds->w)/2*/time.size()*26 ,50, seconds->w,seconds->h);
            
            apply_surface(seconds,screen,/*(SCREEN_WIDTH - seconds->w)/2*/time.size()*26 , 50 );

            SDL_FreeSurface(seconds);
		}

		start_stop.show(screen); //display start_stop button

		SDL_Flip(screen);  //update the screen

    }
return 0;
}
