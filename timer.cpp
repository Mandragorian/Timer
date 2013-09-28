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
        int  start_t;    //gets the time the timer started
        int  paused;     //gets the time when the timer was paused
        int  ellapsedp;  //the ellapsed pause time

        bool running;    //stores the state of the timer (running or not)
        
        static int timers; //static member for keeping track of the no of timers for possible use

    public:
        Timer();

        void start();   //starts timer
        void pause();   //pauses timer
        void stop();    //stops (resets) timer
        void resume();  //resumes paused timer

        int  get_ticks();  //returns the time kept by the timer

        bool is_running(); //returns the state of the timer
};

int Timer::timers = 0;

Timer::Timer()
{
    start_t     = 0;
    paused   	= 0;
    ellapsedp 	= 0;

    running   	= false;
    
    cout << "-Timer No: " << timers++ <<" started!\n";
}

void Timer::start()
{
    start_t   = SDL_GetTicks(); //stores starting time
    running = true;				//and sets the state of the timer to running
}

void Timer::pause()
{
    running = false;		   //sets state to stopped
    paused = SDL_GetTicks();   //and stores the time the timer was paused
}

void Timer::stop()
{
    running = false;		// sets state to not runnin
    start_t   = 0;			//zeroes everything
    paused    = 0;
    ellapsedp = 0;
}

void Timer::resume()
{
    running    = true;     //sets state to running
    ellapsedp += SDL_GetTicks() - paused;  //accumulates ellapsed paused time
}

int Timer::get_ticks()
{
    return SDL_GetTicks() - start_t - ellapsedp; 
}

bool Timer::is_running()
{
    return running;
}
