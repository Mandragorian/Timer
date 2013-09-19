#include"SDL.h"
#include<string>
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<iostream>
#include <sstream>
#include"helpf.h"

using namespace std;

class Timer {

    private:
        int  start_t;
        int  paused;
        int  ellapsedp;

        bool running;
        
        static int timers;

    public:
        Timer();

        void start();
        void pause();
        void stop();
        void resume();

        int  get_ticks();

        bool is_running();
};

int Timer::timers = 0;

Timer::Timer()
{
    start_t     = 0;
    paused   = 0;
    ellapsedp = 0;

    running   = false;
    
    cout << "Timer No: " << timers++ <<" started!\n";
}

void Timer::start()
{
    start_t   = SDL_GetTicks();
    running = true;
}

void Timer::pause()
{
    running = false;
    paused = SDL_GetTicks();
}

void Timer::stop()
{
    running = false;
    start_t   = 0;
    paused    = 0;
    ellapsedp = 0;
}

void Timer::resume()
{
    running    = true;
    ellapsedp += SDL_GetTicks() - paused;
}

int Timer::get_ticks()
{
    return SDL_GetTicks() - start_t - ellapsedp;
}

bool Timer::is_running()
{
    return running;
}
