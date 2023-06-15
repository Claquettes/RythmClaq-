#ifndef animations_h
#define animations_h


#include <SDL2/SDL.h>

class Pannel;

class Animations {
public:
    static void movePannel(Pannel& Pannel, int targetX, int targetY, int duration, SDL_Renderer* renderer);
    static void resizePannel(Pannel& Pannel, int targetWidth, int targetHeight, int duration, SDL_Renderer* renderer);
    static void changeColor(Pannel& Pannel, SDL_Color targetColor, int duration, SDL_Renderer* renderer);
    static void fadeIn(Pannel& Pannel, int duration, SDL_Renderer* renderer);
    static void fadeOut(Pannel& Pannel, int duration, SDL_Renderer* renderer);
    static void fadeInOut(Pannel& Pannel, int duration, SDL_Renderer* renderer);
    static void fadeOutIn(Pannel& Pannel, int duration, SDL_Renderer* renderer);    
};

#endif // ANIMATIONS_H
