#include "note.h"
#include <iostream>
#include <string>
#include <vector>
#include <random> //for the speed of the note
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Note.cpp
Note::Note()
{
    // constructor implementation
    std::cout << "Note constructor called!" << std::endl;
    // we create a rect for the note
    note_rect.x = 0;
    note_rect.y = 200;
    note_rect.w = note_size;
    note_rect.h = note_size;
}

Note::~Note()
{
    // destructor implementation
    std::cout << "Note destructor called!" << std::endl;
}

SDL_Rect Note::getNoteRect() const
{
    return note_rect;
}
