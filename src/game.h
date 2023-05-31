#ifndef GAME_H
#define GAME_H
#include "note.h"
#include "judgementLine.h"
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
        int render();

        //we define the array of notes
        std::vector<Note> notes;

        //we define the judgement line
        JudgementLine judgementLine;
    private:
        bool readyToStart = false;
        // the window we'll be rendering to
        SDL_Window* window;
        SDL_Renderer* renderer;
        // we create the notes
        Note note1;

        double startTime = 0;
        double DELAY_BETWEEN_FRAMES = 10;

        double speed = 1;

        void update();


};

#endif // GAME_H

