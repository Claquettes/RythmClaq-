#include "game.h"
#include "note.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game()
{
    std::cout << "Game constructor called!" << std::endl;
    // we call the init method
    init();
    // we call the gameLoop method once the game is initialized
    while (!readyToStart)
    {
        std::cout << "Initializing game..." << std::endl;
    }
    gameLoop();
}

Game::~Game()
{
    // destructor implementation
    std::cout << "Game destructor called!" << std::endl;
}

int Game::init()
{
    // we initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the window
    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we set the color of the renderer to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // we set the readyToStart flag to true
    readyToStart = true;

    return 0;
}

int Game::gameLoop()
{
    // main loop flag
    bool quit = false;
    // event handler
    SDL_Event e;
    // main loop
    while (!quit)
    {
        // event handling
        while (SDL_PollEvent(&e) != 0)
        {
            // user requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        // clear the screen
        SDL_RenderClear(renderer);

       //we get the note rect
         SDL_Rect note_rect = note1.getNoteRect();
        // we render the note
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &note_rect);

        // update the screen
        SDL_RenderPresent(renderer);
    }
    // free resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
