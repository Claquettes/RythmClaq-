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


    //we check if the pannel has a texture
    if (texture_ != NULL) {
        //we render the image of the pannel, by creating a rect
        SDL_Rect rect = { x_, y_, width_, height_ };
        SDL_RenderCopy(renderer, texture_, NULL, &rect);

    }
    else {
        SDL_Rect rect = { x_, y_, width_, height_ };
        SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
        SDL_RenderFillRect(renderer, &rect);
    }


    
}

void Pannel::setSize(int width, int height) {
    width_ = width;
    height_ = height;
}

void Pannel::setX(int x) {
    x_ = x;
}

void Pannel::setY(int y) {
    y_ = y;
}

void Pannel::loadTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width_, height_, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color_.r, color_.g, color_.b, color_.a));
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Pannel::destroyTexture() {
    SDL_DestroyTexture(texture_);
}

void Pannel::applyTexture(SDL_Renderer* renderer) {
    SDL_Rect rect = { x_, y_, width_, height_ };
    SDL_RenderCopy(renderer, texture_, NULL, &rect);
}

void Pannel::applyImage(SDL_Renderer* renderer, std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect rect = { x_, y_, width_, height_ };
    SDL_RenderCopy(renderer, texture_, NULL, &rect);
}

bool Pannel::isInside(int x, int y) const {
    return x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_; //true if the coordinates are inside the pannel
}