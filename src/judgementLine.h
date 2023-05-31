#ifndef JUDGEMENTLINE_H
#define JUDGEMENTLINE_H
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class JudgementLine {
    public:
        // constructor
        JudgementLine();

        // destructor
        ~JudgementLine();

        //public properties
        const int width = 10;
        const int height = 640;

        //position of the judgement line
        const int x = 50;
        const int y = 0;

        const int applicationPoint = 60;

        SDL_Rect getJudgementLineRect() const; //we add the const keyword to the method, because we don't want to modify the judgement_line_rect
    private:
        //we create a rect to represent the judgement line
        SDL_Rect judgement_line_rect;
};

#endif // JUDGEMENTLINE_H
