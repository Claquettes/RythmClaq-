#include "game.h"
#include "note.h"
#include "judgementLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <SDL2/SDL_ttf.h>

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

    //we free the memory allocated for the textures and surfaces
    SDL_FreeSurface(note1Surface);
    SDL_FreeSurface(note2Surface);

    SDL_DestroyTexture(note1Texture);
    SDL_DestroyTexture(note2Texture);

    //we close the font
    TTF_CloseFont(font);

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
    //we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);

    //We create the surface and texture for the two notes
    note1Surface = IMG_Load("assets/skin/1-note.png");
    note2Surface = IMG_Load("assets/skin/2-note.png");

    note1Texture = SDL_CreateTextureFromSurface(renderer, note1Surface);
    note2Texture = SDL_CreateTextureFromSurface(renderer, note2Surface);

    
    //we initialize SDL_ttf
    TTF_Init();
    //we load the font
    font = nullptr;
    font = TTF_OpenFont("assets/fonts/1up.ttf", 24);
    std::cout << "Font loaded!" << std::endl;
    
    // we set the readyToStart flag to true
    std::cout << "Game initialized!, Launching the gameLoop" << std::endl;
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
           //we render the note
            SDL_RenderCopy(renderer, note1Texture, NULL, &noteRect);
        }
        else if (notes[i].getValue() == 2)
        {
            SDL_RenderCopy(renderer, note2Texture, NULL, &noteRect);
        }
        else 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Error: Note value is not 1 or 2" << std::endl;
        }
    }

    //we render the judgement line
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect judgementLineRect = judgementLine.getJudgementLineRect();
    SDL_RenderFillRect(renderer, &judgementLineRect);
    //we render the score
    renderScore(200, score);

    //we render the changes above
    SDL_RenderPresent(renderer);
    return 0;
}

void Game::update()
{   
    if(numberOfMisses == 5){
        return;
        //WE NEED TO CALL THE ÉNDGAME METHOD HERE
        SDL_Quit();
    }

    if (notes.size() > 2)
    {
        //we check if the first note is out of the screen , and if it is, we delete it
        if (notes[0].getNoteRect().x < 0)
        {
            std::cout << "Deleted " << std::endl;
            notes.erase(notes.begin() + 0); //the +0 is to convert the iterator to an integer
            //we reset the combo and add 1 to the miss counter
            combo = 0;
            numberOfMisses++;
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

        //we check if the file is empty, ie highscore is null
        if (highscore == NULL)
        {
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

void Game::renderScore(int y, double score){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //we create a font
    TTF_Font* fontScore = TTF_OpenFont("data/font/1up.ttf", 24);
    y = 0;
    //we create an int called numberDigits, which is the number of digits in the score
    int numberDigits = 1;
    int scoreCopy = score;
    while (scoreCopy > 10)
    {
        scoreCopy = scoreCopy / 10;
        numberDigits++;
    }
    //we create a char array, which is the same size as the number of digits in the score
    char char_score[numberDigits];
    //we convert the score to a char array
    sprintf(char_score, "%f", score);

    SDL_Color white = {255, 255, 255};
    scoreSurface = TTF_RenderText_Solid(fontScore, char_score, white);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {(WINDOW_WIDTH / 2) - 200, y, 200, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &scoreRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}