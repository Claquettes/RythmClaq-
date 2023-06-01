#include "game.h"
#include "note.h"
#include "judgementLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

//TODO NEXT: SPRITES FOR THE NOTES, AND THE HITS

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
    while (numberOfMisses < 5)
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

                //we calculate the distance from the judgement line, if it's more than 100, we don't hit the note
                int distancePos = notes[0].getX() - 60;
                if (distancePos > 100)
                {
                    std::cout << "To early to count" << std::endl;
                }else {
                    //we call the calculateNoteValue method of the first note, passing the input as a parameter
                    int hit_value = notes[0].calculateNoteValue(e, true);
                    if (hit_value == 0)
                    {
                        std::cout << "Missed!" << std::endl;
                        //we reset the combo
                        combo = 0;
                        //we add 1 to the miss counter
                        numberOfMisses++;
                    }
                    //we add the hit value to the score, multiplying it by the (combo/100 + speed)/2
                    score += hit_value * (combo/100 + speed)/2; //always sum the score, even if the note is missed
                    //we remove the note from the array
                    notes.erase(notes.begin() + 0);
                    //we cout the score
                    std::cout << "Score: " << score << std::endl;
                }
            }
        }
        if (SDL_GetTicks() - startTime > DELAY_BETWEEN_FRAMES) { //sdlticks returns the number of milliseconds since the SDL library was initialized
                startTime = SDL_GetTicks(); // reset the starting time to the current time
                update();
            }
        render();
        
    }
    std::cout << "Game over!" << std::endl;
    std::cout << "Your score is: " << score << std::endl;

    //we call the highscoreManagement method, passing the score as a parameter
    highscoreManagement(score); 


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
    if (notes.size() > 2)
    {
        //we check if the first note is out of the screen , and if it is, we delete it
        if (notes[0].getNoteRect().x < 0)
        {
            std::cout << "Deleted " << std::endl;
            notes.erase(notes.begin() + 0); //the +0 is to convert the iterator to an integer
        }
    }

    //we update the speed of the notes
    speed = speed + SDL_GetTicks() / 50000;

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
            //we add it to the array, at the start of the vector, and not at the end
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

//check if the score is higher than the highscore, and if so update the highscore
void Game::highscoreManagement(double score) { 
    std::ifstream file("highscore.txt"); //we open the file for reading
    if (file.is_open()) {
        double highscore;
        file >> highscore; // Read the highscore from the file

        //if the file is empty, we set the highscore to 0
        if (file.eof()) {
            highscore = 0;
        }
        
        if (score > highscore) {
            std::ofstream outfile("highscore.txt"); // Open the file for writing
            if (outfile.is_open()) {
                outfile << score; // Write the new highscore to the file
                outfile.close(); // Close the file
                std::cout << "New highscore achieved!" << std::endl;
            } else {
                std::cout << "Unable to update highscore file." << std::endl;
            }
        } else {
            std::cout << "No new highscore achieved." << std::endl;
        }

        file.close(); // Close the file
    } else {
        std::cout << "Unable to open highscore file." << std::endl;
    }
}