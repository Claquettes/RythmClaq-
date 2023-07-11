#include "pannel.h"

Pannel::Pannel(int x, int y, int width, int height, SDL_Color color)
    : x_(x), y_(y), width_(width), height_(height), color_(color) {}

int Pannel::getX() const {
    return x_;
}

int Pannel::getY() const {
    return y_;
}

int Pannel::getWidth() const {
    return width_;
}

int Pannel::getHeight() const {
    return height_;
}

SDL_Color Pannel::getColor() const {
    return color_;
}

void Pannel::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Pannel::setWidth(int newWidth) {
    width_ = newWidth;
}

void Pannel::setHeight(int newHeight) {
    height_ = newHeight;
}

void Pannel::setColor(SDL_Color color) {
    color_ = color;
}

//the render function
void Pannel::render(SDL_Renderer* renderer) const {
    SDL_Rect rect = { x_, y_, width_, height_ };
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Pannel::setSize(int width, int height) {
    width_ = width;
    height_ = height;
}