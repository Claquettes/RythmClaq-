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
     
    // constructor
    Game();

    // destructor
    ~Game();
};

#endif // GAME_H
