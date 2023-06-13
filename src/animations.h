#ifndef animations_h
#define animations_h


#include <SDL2/SDL.h>

class Pannel;

class Animations {
public:
    static void movePannel(Pannel& Pannel, int targetX, int targetY, int duration);
    static void resizePannel(Pannel& Pannel, int targetSide, int duration);
    static void changeColor(Pannel& Pannel, SDL_Color targetColor, int duration);
};

#endif // ANIMATIONS_H
