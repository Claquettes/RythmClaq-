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


    //we init the textures and surfaces for the hits
    hit300Surface = IMG_Load("assets/skin/hit300.png");
    hit300Texture = SDL_CreateTextureFromSurface(renderer, hit300Surface);

    hit100Surface = IMG_Load("assets/skin/hit100.png");
    hit100Texture = SDL_CreateTextureFromSurface(renderer, hit100Surface);

    hit50Surface = IMG_Load("assets/skin/hit50.png");
    hit50Texture = SDL_CreateTextureFromSurface(renderer, hit50Surface);

    missSurface = IMG_Load("assets/skin/hit0.png");
    missTexture = SDL_CreateTextureFromSurface(renderer, missSurface);

    // we set the readyToStart flag to true
    std::cout << "Game initialized!, Launching the gameLoop" << std::endl;
    readyToStart = true;
    startTime = SDL_GetTicks();
    spawnManagementSystem();
    return 0;
}

int Game::handleInput()
{
    int hit_value = 0;
    int distancePos = notes[0].getX() - 90;
     //we call the calculateNoteValue method of the first note, passing the input as a parameter
    hit_value = notes[0].calculateNoteValue(distancePos);
                    
    if (hit_value == 0) //miss
    {
    //WE render the miss object
    std::cout << "Missed!" << std::endl;
    //we reset the combo
    combo = 0;
    //we add 1 to the miss counter
    numberOfMisses++;
    render(false, hit_value);
    }
    else{ //NOT MISS
    //we add the hit value to the score, multiplying it by the (funny number, and we floor it
    score += floor(hit_value * (combo/100.69 + speed*1.444)/2.727);
    combo++;
    render(true, hit_value);
    }
    
    //the function to remove the first element of the vector is now called when the event is handled
}
//this function is called when the game is initialized. It will check every 60/8 frames if a note should be spawned, by reading the .claq file
void Game::spawnManagementSystem()
{
    //we empty the vector
    notes.clear();
    //we reset the frame counter
    long frameCounter = 0;
    // we open the file
    std::ifstream file("assets/songs/1.claq");
    std::string line;
    // we read the file line by line and we push the values into the vector
    while (std::getline(file, line))
    {
        //we create the note
        Note note;
        //we convert the string to an double
        double notePos = std::stod(line);
        notePos = notePos * 10 + WINDOW_WIDTH;
        std::cout << "Note position: " << notePos << std::endl;
        //we set the x coordinate of the note
        note.placeNote(notePos);
        //we add the note to the array
        notes.push_back(note);
    }

   
    
}
int Game::gameLoop()
{
    // main loop flag
    bool quit = false;
    bool callHit = false;
    int hit_value = 0;

    Uint32 startTime = SDL_GetTicks();
    int frameTime = 0;


    // event handler
    SDL_Event e;
    // main loop
    while (numberOfMisses < 5)
    {
        frameStart = SDL_GetTicks();
        // event handling
        while (SDL_PollEvent(&e) != 0)
        {
            //if the user presses the any key on the keyboard
            if (e.type == SDL_KEYDOWN)
            {   //we get the length of the array of notes
                int length = notes.size();
                std::cout << "Key pressed!" << std::endl;
                //we call the handleInput method
                handleInput();
                //we remove the first note from the array if the length is greater than 0
                if (length > 0)
                {
                    notes.erase(notes.begin());
                }
                else
                {
                    std::cout << "The array is empty!" << std::endl;
                    //we close the game
                    quit = true;
                    SDL_Quit();
                }
                std::cout << "removing note from array" << "the length of the array is now" << notes.size() << std::endl;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //we update the frame count
        frameCount++;
        // Calculate frame time and delay if needed
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        update();
        render(callHit, hit_value);
    }   
    

    std::cout << "Game over!" << std::endl;
    std::cout << "Your score is: " << score << std::endl;

    //we call the highscoreManagement method, passing the score as a parameter
    highscoreManagement(score); 
    //we call the destructor
    Game::~Game();
    return 0;
}

int Game::render(bool hit, short hitValue)
{
    //if the hitvalue is not 0, we store the hit value in the lastHitValue variable
    if (hitValue != 0)
    {
        int lastHitValue = hitValue;
    }

    //we clear the renderer
    SDL_RenderClear(renderer);
    
    //we render the background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, NULL);

    //we render the judgement line
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect judgementLineRect = judgementLine.getJudgementLineRect();
    SDL_RenderFillRect(renderer, &judgementLineRect);

    //we render the container 
    SDL_SetRenderDrawColor(renderer, 114, 167, 214, 255);
    SDL_Rect containerRect = {50, 150, 750, 150}; //x, y, width, height
    SDL_RenderFillRect(renderer, &containerRect);

    //we render the judgement zone
    SDL_SetRenderDrawColor(renderer, 92, 191, 55, 255);
    SDL_Rect judgementZoneRect = {49, 185, 75, 75}; //x, y, width, height
    SDL_RenderFillRect(renderer, &judgementZoneRect);

    //we create a SDL_Rect for the hit note
    
    SDL_Rect hitRect = {19, 120, 80, 80}; //x, y, width, height

    switch (hitValue)
    {
        case 50:
            SDL_RenderCopy(renderer, hit50Texture, NULL, &hitRect);
            break;
        case 100:
            SDL_RenderCopy(renderer, hit100Texture, NULL, &hitRect);
            break;
        case 300:
            SDL_RenderCopy(renderer, hit300Texture, NULL, &hitRect);
            break;
        default:
            break;
    }

    for (int i = 0; i < notes.size(); i++) 
    {
        //we use the getNoteRect method to get the SDL_Rect of the note
        SDL_Rect noteRect = notes[i].getNoteRect();
        //we render the note in red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &noteRect);
    }

    
    //we render the score
    renderScore(200, score, combo);

    //we render the changes above
    SDL_RenderPresent(renderer);
    return 0;
}

void Game::spawnNotes()
{

    Note newNote;
    newNote.placeNote(WINDOW_WIDTH);
    //we add it to the array, at the start of the vector, and not at the end
    notes.push_back(newNote);
}

void Game::checkDelete()
{
    //we check if the first note is out of the screen , and if it is, we delete it
    if (notes[0].getNoteRect().x < -30)
    {
        std::cout << "Deleted " << std::endl;
        notes.erase(notes.begin() + 0); //the +0 is to convert the iterator to an integer
        //we reset the combo and add 1 to the miss counter
        combo = 0;
        numberOfMisses++;
        return;
    }
}


void Game::update()
{   
    if(numberOfMisses == 5){
        return;
        //WE NEED TO CALL THE ÉNDGAME METHOD HERE
        SDL_Quit();
    }
    //we update the speed of the notes
    speed = speed + 0.0001;

    //we update the notes, by sliding them to the left by 1 pixel
    for (int i = 0; i < notes.size(); i++)
    {   
        //we call the moveNote method on every note
        notes[i].moveNote(speed);
    }
    if (notes.size() > 0)
    {
        checkDelete();
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

void Game::renderScore(int y, double score, short combo){
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

    //we render the combo in the comboRect
    SDL_Rect comboRect = {(WINDOW_WIDTH / 2) - 300, y + 50, 200, 50};
    //we need to transform the combo into a char array, and we add "combo :"
    char char_combo[10];
    sprintf(char_combo, "Combo : %d", combo);

    SDL_Color red = {255, 0, 0};
    comboSurface = TTF_RenderText_Solid(fontScore, char_combo, red);
    comboTexture = SDL_CreateTextureFromSurface(renderer, comboSurface);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &comboRect);
    SDL_RenderCopy(renderer, comboTexture, NULL, &comboRect);
}
