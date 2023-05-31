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
    window = SDL_CreateWindow("RythmClaq", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    
    //we add the notes to the array
    notes.push_back(note1);

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
            //if the user presses the D or K key,  D = red, K = green
            if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_k))
            {
                //we call the calculateNoteValue method of the first note, passing the input as a parameter
                int hit_value = notes[0].calculateNoteValue(e, true);
                //we print the value of the note in the console:
                std::cout << "Note value: " << hit_value << std::endl;
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

    //we render the container 
    SDL_SetRenderDrawColor(renderer, 114, 167, 214, 255);
    SDL_Rect containerRect = {50, 150, 750, 150}; //x, y, width, height
    SDL_RenderFillRect(renderer, &containerRect);

    //we render the judgement zone
    SDL_SetRenderDrawColor(renderer, 92, 191, 55, 255);
    SDL_Rect judgementZoneRect = {19, 185, 75, 75}; //x, y, width, height
    SDL_RenderFillRect(renderer, &judgementZoneRect);


    for (int i = 0; i < notes.size(); i++) 
    {
        //we use the getNoteRect method to get the SDL_Rect of the note
        SDL_Rect noteRect = notes[i].getNoteRect();
        //we check the value, to see if it is 1 or 2, and so change the color of the note
        if (notes[i].getValue() == 1)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else if (notes[i].getValue() == 2)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else 
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        
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
    //we update the speed of the notes
    speed = speed + SDL_GetTicks() / 20000;

    //we update the notes, by sliding them to the left by 1 pixel
    for (int i = 0; i < notes.size(); i++)
    {   
        //we call the moveNote method on every note
        notes[i].moveNote(speed);
    }

    //we MAYBE spawn a new note every BEAT
    if (SDL_GetTicks() % BEAT < precisionToSpawn)
    {
        if (rand() % 100 < (probBeat * 100))
        {
            //we create a new note
            Note newNote;
            newNote.placeNote(WINDOW_WIDTH);
            //we add it to the array
            notes.push_back(newNote);
        }
    }

    //we MAYBE spawn a new note every 1/2 of a beat
    if (SDL_GetTicks() % HALF_BEAT < precisionToSpawn)
    {
        if (rand() % 100 < (probHalfBeat * 100))
        {
            //we create a new note
            Note newNote;
            newNote.placeNote(WINDOW_WIDTH);
            //we add it to the array
            notes.push_back(newNote);
        }
    }

    //we MAYBE spawn a new note every 1/4 of a beat
    if (SDL_GetTicks() % QUARTER_BEAT < precisionToSpawn)
    {
        if (rand() % 100 < (probQuarterBeat * 100))
        {
            //we create a new note
            Note newNote;
            newNote.placeNote(WINDOW_WIDTH);
            //we add it to the array
            notes.push_back(newNote);
        }
    }
    
    //we MAYBE spawn a new note every 1/8 of a beat
    if (SDL_GetTicks() % EIGHTH_BEAT < precisionToSpawn)
    {
        if (rand() % 100 < (probEighthBeat * 100))
        {
            //we create a new note
            Note newNote;
            newNote.placeNote(WINDOW_WIDTH);
            //we add it to the array
            notes.push_back(newNote);
        }
    }


}