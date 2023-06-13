#ifndef Pannel_H
#define Pannel_H

#include <SDL2/SDL.h>

class Pannel {
public:
    Pannel(int x, int y, int width, int height, SDL_Color color);

    //constructor by default
    Pannel() : Pannel(0, 0, 0, 0, { 0, 0, 0, 0 }) {}

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    SDL_Color getColor() const;

    void setPosition(int x, int y);
    void setWidth(int x);
    void setHeight(int y);
    void setColor(SDL_Color color);

    void render(SDL_Renderer* renderer) const;

private:
    int x_;
    int y_;
    int width_;
    int height_;
    SDL_Color color_;
};

#endif // Pannel_H
