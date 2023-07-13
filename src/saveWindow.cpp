#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "saveWindow.h"


// Function to display a message on the SDL window
void SaveWindow::displayMessage(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, int x, int y, SDL_Color color)
{
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
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Saving your Map", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("data/font/arial.ttf", 24);

    SDL_Event event;
    bool quit = false;


    //we call the createPannels function
    createPannels();



    while (!quit)
    {
        //we check if there is an event
        while (SDL_PollEvent(&event))
        {
            //if the event is a click on the cross, we quit the window
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_RenderClear(renderer);
        backgroundPannel.render(renderer);
        topPannel.render(renderer);


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

//we create a function that will place all of the pannels that we need
void SaveWindow::createPannels()
{
    // Top pannel defined in the .h file
    //we set the position of the pannel
    topPannel.setPosition(0, 0);
    topPannel.setSize(SCREEN_WIDTH, 20);
    
    //we set the color of the pannel
    topPannel.setColor(white);
    //we display a text on the pannel
    //we create a string
    std::string text = "Enter Map's Metadata";
    

    std::cout << "topPannel created" << std::endl;


    //background Pannel defined in the .h file
    //we set the position of the pannel
    backgroundPannel.setPosition(0, 0);
    backgroundPannel.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //we set the color of the pannel
    backgroundPannel.setColor(bg);


}