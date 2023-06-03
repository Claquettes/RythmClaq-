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
    note_rect.x = 500;
    note_rect.y = 200;
    note_rect.w = 50;
    note_rect.h = 50;
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
    note_rect.y = 200;
}

int Note::getValue() const
{
    return value;
}

int Note::calculateNoteValue(SDL_Event event, bool isCorrect)
{
    if(!hitable)
    {
        return 0;
    }
    //we check if the event is a keydown event, and if it's the correct key, a value of 1 == the key d needs to be pressed, a value of 2 == the key k needs to be pressed
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d && value == 1)
    {
        isCorrect = true;
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k && value == 2)
    {
        isCorrect = true;
    }
    else
    {
        isCorrect = false;
        return 0;
    }
    
    //now we calculate the score, based on the position of the note
    //we get the position of the note
    int note_position = note_rect.x;
    //we calculate the difference between the note position and the application point
    int difference = abs(note_position - 50 + 4);

    std::cout << "difference: " << difference << std::endl;
    //we calculate the score
    if (difference <= 55 && isCorrect)
    {
        return 300;
    }
    else if (difference <= 100 && isCorrect)
    {
        return 100;
    }
    else if (difference <= 259 && isCorrect)
    {
        return 50;
    }
    else
    {
        return 0;
    }
}

int Note::getX() const
{
    return note_rect.x;
}
