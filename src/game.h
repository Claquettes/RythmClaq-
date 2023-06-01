#ifndef GAME_H
#define GAME_H
#include "note.h"
#include "judgementLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class Game {
    public:
        // size of the window (16:9)
        const int WINDOW_WIDTH = 800; 
        const int WINDOW_HEIGHT = 450;

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
        void removeNote();
        void renderScore(int y, double score);

        //we create the font
        TTF_Font* font;

        //we define the judgement line
        JudgementLine judgementLine;
    private:
        bool readyToStart = false;

        const short precisionToSpawn = 10;
        
        const int BEAT = 1000;
        const int HALF_BEAT = BEAT / 2;
        const int QUARTER_BEAT = BEAT / 4;
        const int EIGHTH_BEAT = BEAT / 8;

        const float probBeat = 0.9;
        const float probHalfBeat = 0.3;
        const float probQuarterBeat = 0.1;
        const float probEighthBeat = 0.05;

        double startTime = 0;
        double DELAY_BETWEEN_FRAMES = 10;
        double speed = 3;
        double score = 0;
        double combo = 0;
        short numberOfMisses = 0;
        int nextNoteToHit = 0;
        // the window we'll be rendering to
        SDL_Window* window;
        SDL_Renderer* renderer;

        //we create the surfaces and textures of the notes
        SDL_Surface* note1Surface;
        SDL_Surface* note2Surface;

        SDL_Texture* note1Texture;
        SDL_Texture* note2Texture;

        SDL_Surface* scoreSurface;
        SDL_Texture* scoreTexture;
        // we create the first note
        Note note1;

        

        void update();
        void highscoreManagement(double score);


};

#endif // GAME_H

