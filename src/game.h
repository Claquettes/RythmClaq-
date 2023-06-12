#ifndef GAME_H
#define GAME_H
#include "note.h"
#include "judgementLine.h"
#include "map.h"
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

        // constructor, who takes a MAP as an argument when called
        Game(Map map);


        // destructor
        ~Game();

        // methods
        int init();
        int gameLoop();
        int render(bool hit, short hitValue);

        //we define the array of notes
        std::vector<Note> notes;
        void removeNote();
        void renderScore(int y, double score, short combo);

        //we create the font
        TTF_Font* font;

        //we define the judgement line
        JudgementLine judgementLine;
    private:
        bool readyToStart = false;
        //the greater the precision, the less notes will spawn
        const short precisionToSpawn = 15;
        
        const int BEAT = 900;
        const int HALF_BEAT = BEAT / 2;
        const int QUARTER_BEAT = BEAT / 4;
        const int EIGHTH_BEAT = BEAT / 8;

        const float probBeat = 0.9;
        const float probHalfBeat = 0.4;
        const float probQuarterBeat = 0.2;

        double startTime = 0;
        double speed = 4;
        double score = 0;
        short combo = 0;
        short numberOfMisses = 0;
        int nextNoteToHit = 0;

        // Variables for regulating frames per second
    const int targetFPS = 60;
    const int frameDelay = 1000 / targetFPS;
    Uint32 frameStart;
    int frameTime;

    // Variables for tracking frame count
    int frameCount = 0;
    int spawnInterval = 50;

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

        SDL_Surface* comboSurface;
        SDL_Texture* comboTexture;

        SDL_Surface* missNumberSurface;
        SDL_Texture* missNumberTexture;

        SDL_Surface* hit300Surface;
        SDL_Texture* hit300Texture;

        SDL_Surface* hit100Surface;
        SDL_Texture* hit100Texture;

        SDL_Surface* hit50Surface;
        SDL_Texture* hit50Texture;

        SDL_Surface* missSurface;
        SDL_Texture* missTexture;

        // we create the rect of the hit 
        SDL_Rect hit_rect2;




        // we create the first note
        Note note1;

        

        void update();
        void highscoreManagement(double score);
        void renderHitNote(short hitValue);
        void spawnNotes();
        void checkDelete();
        int handleInput();
        void spawnManagementSystem();


        

};

#endif // GAME_H

