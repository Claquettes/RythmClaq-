#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream> //for file manipulation
#include <cmath> //use to round numbers, useful for snapping notes to the grid

#include "saveWindow.h"
#include "editor.h"






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
    TTF_Font* font = TTF_OpenFont("data/font/arial.ttf", 20);

    SDL_Event event;
    bool quit = false;
    //we call the createPannels function
    createPannels();

    //we create a vaar that will contain the current selected panel
    currentPanel = "namePannelInput";
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
            //if the event is a click on the mouse, We check if the mouse is on the namePannelInput
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > namePannelInput.getX() && x < namePannelInput.getX() + namePannelInput.getWidth() && y > namePannelInput.getY() && y < namePannelInput.getY() + namePannelInput.getHeight())
                {
                    std::cout << "namePannelInput clicked" << std::endl;
                    //we create a string that will contain the name of the map
                    currentPanel = "namePannelInput";
                    
                }
                if (x > creatorPannelInput.getX() && x < creatorPannelInput.getX() + creatorPannelInput.getWidth() && y > creatorPannelInput.getY() && y < creatorPannelInput.getY() + creatorPannelInput.getHeight())
                {
                    std::cout << "creatorPannelInput clicked" << std::endl;
                    currentPanel = "creatorPannelInput";
                }
                if (x > bpmPannelInput.getX() && x < bpmPannelInput.getX() + bpmPannelInput.getWidth() && y > bpmPannelInput.getY() && y < bpmPannelInput.getY() + bpmPannelInput.getHeight())
                {
                    std::cout << "bpmPannelInput clicked" << std::endl;
                    currentPanel = "bpmPannelInput";
                }
                //we check if the mouse is on the save pannel
                if (x > savePannel.getX() && x < savePannel.getX() + savePannel.getWidth() && y > savePannel.getY() && y < savePannel.getY() + savePannel.getHeight())
                {
                    if(name == "")
                    {
                        std::cout << "Please enter a name" << std::endl;
                    }
                    else if(creator == "")
                    {
                        std::cout << "Please enter a creator" << std::endl;
                    }
                    else if(bpm == "")
                    {
                        std::cout << "Please enter a bpm" << std::endl;
                    }
                    else
                    {
                        std::cout << "Save clicked" << std::endl;
                        save(positions, name, creator, bpm);
                    }
                }
            }
            //if the event is a key pressed
            if (event.type == SDL_KEYDOWN)
            {
                //we check if the key pressed is a letter
                if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
                {
                    //we add the letter to the name of the string using the currentPanel variable
                    if (currentPanel == "namePannelInput")
                    {
                        name += event.key.keysym.sym;
                    }
                    if (currentPanel == "creatorPannelInput")
                    {
                        creator += event.key.keysym.sym;
                    }
                }
                //we check if the key pressed is a number
                if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                {
                    //we add the number to the name of the string using the currentPanel variable
                    if (currentPanel == "bpmPannelInput")
                    {
                        bpm += event.key.keysym.sym;
                    }
                }
                TODO://CHANGE THE IF FOR AN ENUM SO THAT WE CAN USE A SWITCH
                if(currentPanel == "namePannelInput")
                {
                    std::cout << name << std::endl;
                }
                else if(currentPanel == "creatorPannelInput")
                {
                    std::cout << creator << std::endl;
                }
                else if(currentPanel == "bpmPannelInput")
                {
                    std::cout << bpm << std::endl;
                }
            }
            
            
        }
        renderManager(renderer, font);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

//we create a function that will place all of the pannels that we need
void SaveWindow::createPannels()
{
    // Top pannel defined in the .h file
    //we set the position of the pannel
    topPannel.setPosition(0, 0);
    topPannel.setSize(SCREEN_WIDTH, 25);
    
    //we set the color of the pannel
    topPannel.setColor(white);
    //we display a text on the pannel

    std::cout << "topPannel created" << std::endl;

    //background Pannel defined in the .h file
    //we set the position of the pannel
    backgroundPannel.setPosition(0, 0);
    backgroundPannel.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    //we set the color of the pannel
    backgroundPannel.setColor(bg);
    
    std::cout << "backgroundPannel created" << std::endl;

    //we set the position of the pannel, just under the top pannel
    namePannelText.setPosition(0, 25);
    namePannelText.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    namePannelText.setColor(accent);

    std::cout << "namePannelText created" << std::endl;

    //we set the position of the pannel, just under the top pannel
    namePannelInput.setPosition(SCREEN_WIDTH/2, 25);
    namePannelInput.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    namePannelInput.setColor(accentDark);

    std:: cout << "namePannelInput created" << std::endl;
    creatorPannelText.setPosition(0, 55);
    creatorPannelText.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    creatorPannelText.setColor(accent);

    creatorPannelInput.setPosition(SCREEN_WIDTH/2, 55);
    creatorPannelInput.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    creatorPannelInput.setColor(accentDark);

    bpmPannelText.setPosition(0, 85);
    bpmPannelText.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    bpmPannelText.setColor(accent);

    bpmPannelInput.setPosition(SCREEN_WIDTH/2, 85);
    bpmPannelInput.setSize(SCREEN_WIDTH/2, 25);
    //we set the color of the pannel
    bpmPannelInput.setColor(accentDark);
    
    savePannel.setPosition(0, 115);
    savePannel.setSize(SCREEN_WIDTH, 25);
    //we set the color of the pannel
    savePannel.setColor(accentDark);



    //we add all of the pannels to the vector of pannels
    pannels.push_back(topPannel);
    pannels.push_back(backgroundPannel);
    pannels.push_back(namePannelText);
    pannels.push_back(namePannelInput);
    pannels.push_back(creatorPannelText);
    pannels.push_back(creatorPannelInput);
    pannels.push_back(bpmPannelText);
    pannels.push_back(bpmPannelInput);


}

void SaveWindow::renderPannels(SDL_Renderer* renderer)
{
    //we render all of the pannels using the pannels vector
    for (int i = 0; i < pannels.size(); i++)
    {
        pannels[i].render(renderer);
    }

}

void SaveWindow::renderText(SDL_Renderer* renderer, TTF_Font* font)
{
    //we render all of the text
    displayMessage(renderer, font, "Enter Map's Metadata", 10, 0, black);
    displayMessage(renderer, font, "Name:", 10, 25, black);
    displayMessage(renderer, font, "Creator:", 10, 55, black);
    displayMessage(renderer, font, "BPM:", 10, 85, black);  
    displayMessage(renderer, font, "Save", 10, 115, black);
}

void SaveWindow::renderManager(SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_RenderClear(renderer);
    //we render all of the pannels
    renderPannels(renderer); 

    //we render all of the text
    renderText(renderer, font);

    //we render the window
    SDL_RenderPresent(renderer);
}

//we define the destructor
SaveWindow::~SaveWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void SaveWindow::save(std::vector<short unsigned int> positions, std::string name, std::string creator, std::string bpm)
{
    std::cout << "Saving the map" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Creator: " << creator << std::endl;
    std::cout << "BPM: " << bpm << std::endl;
    std::cout << "Positions: " << positions.size() << std::endl;
    // we generate the id of the map. We try with 1, if it already exists, we increment it by 1 until we find an id that doesn't exist
    int id = 1;
    // we check if a folder with the same name already exists
    while (std::filesystem::exists("maps/" + std::to_string(id)))
    {
        std::cout << "A map with the id " << id << " already exists, incrementing the id..." << std::endl;
        id++;
    }
    // Create a folder with the map name
    std::string command = "cd maps && mkdir " + std::to_string(id);
    system(command.c_str());

    // Create or open the info.txt file
    std::ofstream info_file("maps/" + std::to_string(id) + "/infos.txt");
    // Check if the file was successfully opened
    if (info_file.is_open())
    {
        // Write data to the file
        info_file << name << std::endl
                  << creator << std::endl
                  << bpm << std::endl;
        // Close the file
        info_file.close();
    }
    else
    {
        std::cout << "Something went wrong while creating the infos.txt file!" << std::endl;
    }
    // we create the .claq file
    std::ofstream claq_file("maps/" + std::to_string(id) + "/notes.claq");
    std::cout << "Map created!, Now lets place the notes!" << std::endl;
    // for that we use the positions vector
    for (int i = 0; i < positions.size(); i++)
    {
    
        claq_file << positions[i]<< std::endl;
        //we go to the next line
        
    }
    // we close the file
    claq_file.close();
    std::cout << "Notes placed!" << std::endl;
    std::cout << "Map saved! AT maps/" << id << std::endl;
    std::cout << "Exiting the editor..." << std::endl;
    exit(0);
}