#ifndef saveWindow_h
#define saveWindow_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

class SaveWindow{
    public:
    //constructor, with as parameters a vector of int (representing the positions of the notes)
    SaveWindow(std::vector<short unsigned int> positions);
    //destructor
    ~SaveWindow();
    void displayMessage(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, int x, int y);
    
};

#endif // saveWindow_h
