#include "game.h"
#include "note.h"
#include "judgementLine.h"
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
    // free resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Game::init()
{   //we need to reset the RANDOM SEED
    srand(time(NULL)); 

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
    //we place the judgement line
    
    
    // we set the readyToStart flag to true
    readyToStart = true;
    startTime = SDL_GetTicks();
    

    return 0;
}

int Game::gameLoop()
{
    // main loop flag
    bool quit = false;

    //we create the notes
    Note note1;
    Note note2;
    Note note3;
    Note note4;

    //we add the notes to the array
    notes.push_back(note1);
    notes.push_back(note2);
    notes.push_back(note3);
    notes.push_back(note4);

    //for testing purposes, we print the size of the array
    std::cout << "Size of the array: " << notes.size() << std::endl;

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
        if (SDL_GetTicks() - startTime > DELAY_BETWEEN_FRAMES) { //sdlticks returns the number of milliseconds since the SDL library was initialized
                startTime = SDL_GetTicks(); // reset the starting time to the current time
                update();
            }
        render();
        
    }
    //we call the destructor
    Game::~Game();
    return 0;
}

int Game::render(){
    //we clear the screen
    SDL_RenderClear(renderer);
    
    //we render the background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, NULL);

    //we render the notes present in the array
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < notes.size(); i++) 
    {
        //we use the getNoteRect method to get the SDL_Rect of the note
        SDL_Rect noteRect = notes[i].getNoteRect();
        SDL_RenderFillRect(renderer, &noteRect);
    }

    //we render the judgement line
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect judgementLineRect = judgementLine.getJudgementLineRect();
    SDL_RenderFillRect(renderer, &judgementLineRect);

    //we render the changes above
    SDL_RenderPresent(renderer);
    return 0;
}

void Game::update()
{   
    std::cout << "Update tick" << std::endl;

    //we update the speed of the notes
    speed = speed + SDL_GetTicks() / 1000;

    //we update the notes, by sliding them to the left by 1 pixel
    for (int i = 0; i < notes.size(); i++)
    {
        //we call the moveNote method on every note
        notes[i].moveNote(speed);
        //we cout the x position of the note
        std::cout << "Note " << i << " x position: " << notes[i].getNoteRect().x << std::endl;
    }
}