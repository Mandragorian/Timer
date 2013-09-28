#pragma once

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

