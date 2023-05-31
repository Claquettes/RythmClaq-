#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game {
    public:
        // size of the window
        const int WINDOW_WIDTH = 640;
        const int WINDOW_HEIGHT = 480;

        // constructor
        Game();

        // destructor
        ~Game();

        // methods
        int init();
        int gameLoop();
    private:
        bool readyToStart = false;
        // the window we'll be rendering to
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif // GAME_H

