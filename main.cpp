#include"SDL.h"
#include<string>
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<iostream>
#include <sstream>
#include"helpf.h"

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

//class Button {
//   
//    private:
//    //The attributes of the button
//    SDL_Rect box;
//    //The part of the button sprite sheet that will be shown
//    SDL_Rect* clip;
//    
//    SDL_Surface* buttonSheet;    
//    public:
//    //Initialize the variables
//    Button( int x, int y, int w, int h,string img);
//                       
    //Handles events and set the button's sprite region
//    void handle_events();
                            
    //Shows the button on the screen
//    void show();
    
//};

//Button::Button(int x, int y, int w, int h,string img)
//{
//    box.x=x;
//    box.y=y;
//    box.w=w;
//    box.h=h;

//    clip =&clips[CLIP_MOUSEOUT];

//    buttonSheet= load_image(img);
//    if(buttonSheet) cout << "yay!\n";
//}

//void Button::handle_events()
//{
//    int x =0;
//    int y =0;

//    if(event.type == SDL_MOUSEMOTION)
//    {
//        x = event.motion.x;
//        y = event.motion.y;

//        if((x>box.x) && (x < box.x +box.w) && (y > box.y)&&(y<box.y+box.h))
//        {
//            clip = &clips[CLIP_MOUSEOVER];
            //cout << "mouseover\n";
//        }
//        else
//        {
//            clip=&clips[CLIP_MOUSEOUT];
//        }
//    }

//    if(event.type == SDL_MOUSEBUTTONDOWN)
//    {
//        if(event.button.button == SDL_BUTTON_LEFT)
//        {
//            x = event.button.x;
//            y = event.button.y;

//           if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
//            {
//                clip=&clips[CLIP_MOUSEDOWN];
//            }
//        }
//    }
//    else
//    {
//        if(event.button.button == SDL_BUTTON_LEFT)
//        {
//            x = event.button.x;
//            y = event.button.y;

//            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
//            {
//                clip=&clips[CLIP_MOUSEUP];
//            }
//        }
//    }
//}

//void Button::show()
//{
//    apply_surface(buttonSheet,screen,box.x,box.y,clip);
//}


//SDL_Surface *load_image(string filename)
//{
//   SDL_Surface* loaded_img = nullptr;
//   SDL_Surface* opt_img    = nullptr;

//   loaded_img= IMG_Load(filename.c_str());

//   if( loaded_img )
//  {
//       opt_img = SDL_DisplayFormat (loaded_img);
//       SDL_FreeSurface( loaded_img);
//   }

//   return opt_img;

//}

//void apply_surface(SDL_Surface* source, SDL_Surface* destination,int x=0,int y=0, SDL_Rect* clip = nullptr)
//{
//    SDL_Rect offset;

//    offset.x=x;
//    offset.y=y;

//    SDL_BlitSurface(source, clip,destination, &offset);
//}

bool init()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

    if(!screen) return false;

    if( TTF_Init() == -1) return false;
    
    SDL_WM_SetCaption("Event test", nullptr);

    font = TTF_OpenFont("Impact.ttf",20);

    background = load_image("back.png");

    return true;
    
}

int main (int argc, char* args[])
{
    bool quit = false;
    bool running = false;
    
    Uint32 start =0;

    if(!init()) return 1;

    start = SDL_GetTicks();
    
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT) quit = true;
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_s)
                {
                    if(running)
                    {
                        running = false;
                        start =0;
                    }
                    else
                    {
                        running = true;
                        start = SDL_GetTicks();
                    }
                }
            }
                
        }
        if(running)
        {
            stringstream timer;
            SDL_Surface* seconds=nullptr;
            string time="";

            timer <<  (SDL_GetTicks() -start)/1000 ;
            timer >> time;
            
            apply_surface(background,screen,clip.x,clip.y,&clip);


            seconds = TTF_RenderText_Solid(font, time.c_str(),textColour);

            clip = set_clip((SCREEN_WIDTH -seconds->w)/2 ,50, seconds->w,seconds->h);
            
            apply_surface(seconds,screen,(SCREEN_WIDTH - seconds->w)/2 , 50 );

            SDL_FreeSurface(seconds);

            SDL_Flip(screen);



        }

    }
return 0;
}
