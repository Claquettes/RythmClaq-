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
    

    // we create a rect for the note, with random int values between 0 and 300
    note_rect.x = 500;
    note_rect.y = 170;
    note_rect.w = 80;
    note_rect.h = 80;
}

Note::~Note()
{
    
}

SDL_Rect Note::getNoteRect() const
{
    return note_rect;
}

void Note::moveNote(int speed)
{
    //we move the note
    note_rect.x -= speed *2;
}

void Note::placeNote(double xpos)
{
    //we place the note
    note_rect.x = xpos;
    note_rect.y = 170;
}

int Note::getValue() const
{
    return value;
}

int Note::calculateNoteValue(int distance)
{

    //we calculate the score
    if (distance <= 70)
    {
        std::cout << "the note returns 300 points" << std::endl;
        return 300;
    }
    else if (distance <= 100)
    {
        std::cout << "the note returns 100 points" << std::endl;
        return 100;
    }
    else if(distance <= 150)
    {   std::cout << "the note returns 50 points" << std::endl;
        return 50;
    }
    else
    {   std::cout << "the note returns 0 points" << std::endl;
        return 0;
    }
}

int Note::getX() const
{
    return note_rect.x;
}
