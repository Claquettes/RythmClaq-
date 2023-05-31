#ifndef JUDGEMENTLINE_H
#define JUDGEMENTLINE_H
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class JudgementLine {
    public:
        // size of the judgement line
        const int JUDGEMENT_LINE_WIDTH = 640;
        const int JUDGEMENT_LINE_HEIGHT = 10;

        //position of the judgement line
        const int JUDGEMENT_LINE_X = 50;
        const int JUDGEMENT_LINE_Y = 200;
        // constructor
        JudgementLine();

        // destructor
        ~JudgementLine();


        SDL_Rect getJudgementLineRect() const; //we add the const keyword to the method, because we don't want to modify the judgement_line_rect
    private:
        //we create a rect to represent the judgement line
        SDL_Rect judgement_line_rect;
        //we create the getJudgementLineRect method
        
};

#endif // JUDGEMENTLINE_H
