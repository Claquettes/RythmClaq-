#include "song_selection_menu.h"
#include "game.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dirent.h>

//constructor
Song_selection_menu::Song_selection_menu(){
    std::cout << "Song_selection_menu constructor called!" << std::endl;
    //we initialize the Song_selection_menu
    init();
}

//destructor
Song_selection_menu::~Song_selection_menu(){
    std::cout << "Song_selection_menu destructor called!" << std::endl;
    //we free all of the textures and surfaces
    SDL_DestroyTexture(background_texture);
    //we close the Song_selection_menu window
    SDL_DestroyRenderer(renderer_song_selection_menu);
    SDL_DestroyWindow(window_song_selection_menu);
    //we quit SDL
    SDL_Quit();
}

int Song_selection_menu::init(){
    std::cout << "Song_selection_menu init called!" << std::endl;
    // we initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the window
    window_song_selection_menu = SDL_CreateWindow("RythmClaq-Song_selection_menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_song_selection_menu == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the renderer
    renderer_song_selection_menu = SDL_CreateRenderer(window_song_selection_menu, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_song_selection_menu == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    //we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);
    // we load the background image
    background_texture = IMG_LoadTexture(renderer_song_selection_menu, "assets/menu/song_selection_menu/song.png");
    // we render the background
    SDL_RenderCopy(renderer_song_selection_menu, background_texture, NULL, NULL);
    // we update the screen
    SDL_RenderPresent(renderer_song_selection_menu);

    if (background_texture  == nullptr)
    {
        std::cout << "Background could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling Song_selection_menuLoop." << std::endl;
    //
    song_selection_menuLoop();
    return 0;
}

void Song_selection_menu::song_selection_menuLoop(){
    std::cout << "Song_selection_menuLoop called!" << std::endl;
    // we create a boolean that will be true until the user closes the menu
    bool quit = false;
    // we create an event handler
    SDL_Event e;
    // we create a rect that will act as a test button
    SDL_Rect test_rect;
    test_rect.x = 1000;
    test_rect.y = 800;
    test_rect.w = 100;
    test_rect.h = 100;
    
    //we call the refreshMapList function
    refreshMapList();
    
    //we draw the test button
    SDL_SetRenderDrawColor(renderer_song_selection_menu, 223, 112, 78, 255);
    SDL_RenderFillRect(renderer_song_selection_menu, &test_rect);
    SDL_RenderPresent(renderer_song_selection_menu);

    //we listen to events, and we close the menu if the user clicks on the test button
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // if the user clicks on the test button, we close the menu
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= test_rect.x && e.button.x <= test_rect.x + test_rect.w && e.button.y >= test_rect.y && e.button.y <= test_rect.y + test_rect.h)
            {
                //we start the game:
                Game game;
            }
            // if the user clicks on the close button, we close the menu
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }    
}

int Song_selection_menu::refreshMapList() {
    DIR *dir;
    struct dirent *ent;
    std::vector<Map> mapVector; // Store the Map objects

    if ((dir = opendir("maps")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && std::string(ent->d_name) != "." && std::string(ent->d_name) != "..") {
                std::string folderPath = std::string("maps/") + ent->d_name;
                std::ifstream file((folderPath + "/infos.txt").c_str());

                if (file.is_open()) {
                    Map mapObject; // Create a Map object for each directory
                    std::string line;

                    // Read the first line as the name
                    if (std::getline(file, line)) {
                        mapObject.name = line;
                    }

                    // Read the second line as the creator
                    if (std::getline(file, line)) {
                        mapObject.creator = line;
                    }

                    // Add the map object to the vector
                    mapVector.push_back(mapObject);

                    file.close();
                } else {
                    std::cerr << "Failed to open " << folderPath << "/infos.txt" << std::endl;
                }
            }
        }
        closedir(dir);
    } else {
        perror("");
        return EXIT_FAILURE;
    }

    // Process the mapVector vector as needed
    std::cout << "Number of maps: " << mapVector.size() << std::endl;
    std::cout << "List of maps loaded:" << std::endl;
    for (const Map& map : mapVector) {
        // Do something with each Map object
        std::cout << "Name: " << map.name << ", Creator: " << map.creator << std::endl;
    }

    return EXIT_SUCCESS;
}
