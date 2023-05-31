#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Note {
    public:
        //we define the value of the note, using an enum
        enum note_value {
            unatributed = 0,
            pink = 1,  //rgb(230, 25, 222)
            green = 2, //rgb(25, 230, 33)
        };
        // size of the note

        int value = 0;
        const int note_size = 50;

        // constructor
        Note();

        // destructor
        ~Note();

        // methods
        void spawnNote();
        void moveNote();
        void update(double delta);

        SDL_Rect getNoteRect() const; //we add the const keyword to the method, because we don't want to modify the note_rect
    private:
        int x = 0;
        int y = 0;
        const int speed = 1;
        //we create a rect to represent the note
        SDL_Rect note_rect;
        //we create the getNoteRect method
        

};

#endif // GAME_H

