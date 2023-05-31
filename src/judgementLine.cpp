#include "judgementLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

JudgementLine::JudgementLine(){
    std::cout << "JudgementLine constructor called!" << std::endl;
}

JudgementLine::~JudgementLine(){
    std::cout << "JudgementLine destructor called!" << std::endl;
}

SDL_Rect JudgementLine::getJudgementLineRect() const
{
    return judgement_line_rect;
}