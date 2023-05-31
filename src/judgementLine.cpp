#include "judgementLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

JudgementLine::JudgementLine(){
    std::cout << "JudgementLine constructor called!" << std::endl;

    //we initialize the judgement line rect
    judgement_line_rect.x = x;
    judgement_line_rect.y = y;
    judgement_line_rect.w = width;
    judgement_line_rect.h = height;
}

JudgementLine::~JudgementLine(){
    std::cout << "JudgementLine destructor called!" << std::endl;
}

SDL_Rect JudgementLine::getJudgementLineRect() const
{
    return judgement_line_rect;
}