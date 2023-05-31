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
    //we add a value to the note, either 1 or 2
    value = rand() % 2 + 1;
    
    // we create a rect for the note, with random int values between 0 and 300
    note_rect.x = rand() % 300;
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

void Note::moveNote(int speed)
{
    //we move the note
    note_rect.x -= speed;
}

void Note::placeNote(double xpos)
{
    //we place the note
    note_rect.x = xpos;
    note_rect.y = 200;
}

int Note::getValue() const
{
    return value;
}