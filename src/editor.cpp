#include "editor.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <fstream> //for file manipulation

// constructor
Editor::Editor()
{
    std::cout << "Editor constructor called!" << std::endl;
    // we initialize the editor
    init();
}

// destructor
Editor::~Editor()
{
    std::cout << "Editor destructor called!" << std::endl;
    // we free all of the textures and surfaces
    SDL_DestroyTexture(background_texture);
    // we close the editor window
    SDL_DestroyRenderer(renderer_editor);
    SDL_DestroyWindow(window_editor);
    // we quit SDL
    SDL_Quit();
}

int Editor::init()
{
    std::cout << "Editor init called!" << std::endl;
    // we initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the window
    window_editor = SDL_CreateWindow("RythmClaq-Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_editor == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the renderer
    renderer_editor = SDL_CreateRenderer(window_editor, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_editor == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);
    // we load the background image
    background_texture = IMG_LoadTexture(renderer_editor, "assets/menu/editor/editor.png");
    // we render the background
    SDL_RenderCopy(renderer_editor, background_texture, NULL, NULL);
    // we update the screen
    SDL_RenderPresent(renderer_editor);
    if (background_texture == nullptr)
    {
        std::cout << "Background could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling editorLoop." << std::endl;
    editorLoop();
    return 0;
}

void Editor::editorLoop()
{
    std::cout << "editorLoop called!" << std::endl;
    // we create a boolean that will be true until the user closes the menu
    bool quit = false;
    // we create an event handler
    SDL_Event e;
    // we create a rect that will act as a test button
    SDL_Rect test_rect;
    test_rect.x = 100;
    test_rect.y = 100;
    test_rect.w = 100;
    test_rect.h = 100;
    // we draw the test button
    SDL_SetRenderDrawColor(renderer_editor, 223, 12, 78, 255);
    SDL_RenderFillRect(renderer_editor, &test_rect);
    SDL_RenderPresent(renderer_editor);
    editorCli();

    // we listen to events, and we close the menu if the user clicks on the test button
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // if the user clicks on the test button, we close the menu
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= test_rect.x && e.button.x <= test_rect.x + test_rect.w && e.button.y >= test_rect.y && e.button.y <= test_rect.y + test_rect.h)
            {
                quit = true;
            }
            // if the user clicks on the close button, we close the menu
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
}
int Editor::editorCli()
{
    std::cout << "Welcome to the RythmClaq editor!" << std::endl;

    std::cout << "What do you want to do?" << std::endl;
    std::cout << "1. Create a new map" << std::endl;
    std::cout << "2. Edit an existing map" << std::endl;
    // std::cout << "3. Delete a map" << std::endl;

    int choice;
    std::cin >> choice;
    // we need to define the variables here because of the switch, we can't define them in the cases
    std::string path;
    std::string map_name;
    std::string artist_name;
    std::string author_name;
    unsigned short bpm;

    switch (choice)
    {
    case 1:
        std::cout << "You chose to create a new map!" << std::endl;
        std::cout << "Lets create a new map!" << std::endl;
        std::cout << "What is the name of your map?" << std::endl;
        std::cin >> map_name;
        std::cout << "What is the name of the song's artist?" << std::endl;
        std::cin >> artist_name;
        std::cout << "What is your name?" << std::endl;
        std::cin >> author_name;
        std::cout << "What is the BPM of the song?" << std::endl;
        std::cin >> bpm;
        std::cout << "Nice, creating the map..." << std::endl;
        // we'll do the path of the map later.
        path = "path"; // default path for now
        createMap(map_name, artist_name, author_name, bpm, "path");
        break;
    case 2:
        std::cout << "You chose to edit an existing map!" << std::endl;
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }
}

// we define the createMap function

void Editor::createMap(std::string map_name, std::string artist_name, std::string author_name, unsigned short bpm, std::string path)
{

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
    std::ofstream info_file("maps/" + std::to_string(id) + "/info.txt");
    // Check if the file was successfully opened
    if (info_file.is_open())
    {
        // Write data to the file
        info_file << map_name << std::endl
                  << artist_name << std::endl
                  << author_name << std::endl
                  << bpm << std::endl;
        // Close the file
        info_file.close();
    }
    else
    {
        // Failed to open the file
        // Handle the error accordingly
        // For example, display an error message or throw an exception
    }
    // we create the .claq file
    std::ofstream claq_file("maps/" + map_name + "/notes.claq");
    command = "cd ../";
    system(command.c_str());
}
