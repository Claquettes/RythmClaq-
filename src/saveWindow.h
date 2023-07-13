#ifndef saveWindow_h
#define saveWindow_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "pannel.h"

class SaveWindow{
    public:
    //constructor, with as parameters a vector of int (representing the positions of the notes)
    SaveWindow(std::vector<short unsigned int> positions);
    //destructor
    ~SaveWindow();
    void displayMessage(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, int x, int y, SDL_Color color );
    //we create a function that will place all of the pannels that we need
    void createPannels();

    //we create a vector of pannels
    std::vector<Pannel> pannels;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    private:
    Pannel topPannel;
    Pannel backgroundPannel;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color bg = { 189, 189, 189, 255 };
    SDL_Color black = { 0, 0, 0, 255 };
};

#endif // saveWindow_h
