#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game()
{
    std::cout << "Game constructor called!" << std::endl;

}

Game::~Game() {
    // destructor implementation
    std::cout<< "Game destructor called!" << std::endl;
}