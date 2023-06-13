#include "pannel.h"

Pannel::Pannel(int x, int y, int side, SDL_Color color)
    : x_(x), y_(y), side_(side), color_(color) {}

int Pannel::getX() const {
    return x_;
}

int Pannel::getY() const {
    return y_;
}

int Pannel::getSide() const {
    return side_;
}

SDL_Color Pannel::getColor() const {
    return color_;
}

void Pannel::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Pannel::setSide(int side) {
    side_ = side;
}

void Pannel::setColor(SDL_Color color) {
    color_ = color;
}
