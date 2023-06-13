#ifndef Pannel_H
#define Pannel_H

#include <SDL2/SDL.h>

class Pannel {
public:
    Pannel(int x, int y, int side, SDL_Color color);

    int getX() const;
    int getY() const;
    int getSide() const;
    SDL_Color getColor() const;

    void setPosition(int x, int y);
    void setSide(int side);
    void setColor(SDL_Color color);

private:
    int x_;
    int y_;
    int side_;
    SDL_Color color_;
};

#endif // Pannel_H
