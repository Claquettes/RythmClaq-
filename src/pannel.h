#ifndef Pannel_H
#define Pannel_H

#include <SDL2/SDL.h>

class Pannel {
public:
    Pannel(int x, int y, int width, int height, SDL_Color color);

    //constructor by default
    Pannel() : Pannel(0, 0, 0, 0, { 0, 0, 0, 0 }) {}

    //return the x position of the pannel
    int getX() const;
    //return the y position of the pannel
    int getY() const;
    //set the x position of the pannel
    void setX(int x);
    //set the y position of the pannel
    void setY(int y);
    //return the width of the pannel
    int getWidth() const;
    //return the height of the pannel
    int getHeight() const;
    //return the color of the pannel
    SDL_Color getColor() const;

    //set the position of the pannel, by passing two ints as parameters(x and y)
    void setPosition(int x, int y);
    //set the size of the pannel, by passing two ints as parameters(width and height)
    void setSize(int width, int height);
    //set the width of the pannel, by passing an int as parameter
    void setWidth(int x);
    //set the height of the pannel, by passing an int as parameter
    void setHeight(int y);
    //define the color of the pannel, by passing a SDL_Color as parameter
    void setColor(SDL_Color color);

    //render an instance of Pannel, with the renderer passed as parameter
    void render(SDL_Renderer* renderer) const;

private:
    int x_;
    int y_;
    int width_;
    int height_;
    SDL_Color color_;
};

#endif // Pannel_H
