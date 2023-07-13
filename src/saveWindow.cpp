#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "saveWindow.h"


// Function to display a message on the SDL window
void SaveWindow::displayMessage(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, int x, int y)
{
    SDL_Color color = { 255, 255, 255 }; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

SaveWindow::SaveWindow(std::vector<short unsigned int> positions)
{   
    std::cout << "SaveWindow constructor called with this number of positions: " << positions.size() << std::endl;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Player Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("data/font/arial.ttf", 24);

    SDL_Event event;
    bool quit = false;


    while (!quit)
    {


    
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

}

//destructor!
SaveWindow::~SaveWindow()
{
    SDL_Quit();
}