#include "song_selection_menu.h"

#include "game.h" //to start games
#include "map.h" //to interract with maps
#include "pannel.h" //to draw pannels
#include "animations.h" //to draw animations


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
    srand(time(NULL));
    std::cout << "Song_selection_menu init called!" << std::endl;
    // we initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the window
    window_song_selection_menu = SDL_CreateWindow("RythmClaq-Song Selection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

    if (background_texture  == nullptr)
    {
        std::cout << "Background could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    TTF_Init();

    //we check if ttfont is loaded
    if (TTF_Init() < 0)
    {
        std::cout << "TTF could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    font = nullptr;
    font = TTF_OpenFont("data/font/akira.otf", 14);
    std::cout << "Font loaded!" << std::endl;

    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling Song_selection_menuLoop." << std::endl;
    //
    refreshMapList();
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
    test_rect.x = WINDOW_WIDTH / 2 - 50;
    test_rect.y = WINDOW_HEIGHT / 2 - 50;
    test_rect.w = 100;
    test_rect.h = 100;
        
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
                Game game(mapVector[0]);
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

                //the name of the folder is the id of the map
                std::string id = ent->d_name;
                int id_int = std::stoi(id);
                if (file.is_open()) {
                    Map mapObject; // Create a Map object for each directory
                    std::string line;
                    mapObject.id = id_int;

                    // Read the first line as the name
                    if (std::getline(file, line)) {
                        mapObject.name = line;
                    }
                    // Read the second line as the creator
                    if (std::getline(file, line)) {
                        mapObject.creator = line;
                    }
                    if (std::getline(file, line)) {
                        mapObject.artist_name = line;
                    }
                    // Read the third line as the BPM
                    if (std::getline(file, line)) {
                        mapObject.bpm = std::stoi(line);
                    }
                    std::cout << "The bug is not here" << std::endl;
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
    std::cout << "Map list refreshed." << std::endl;
    std::cout << "There are " << mapVector.size() << " maps." << std::endl;
   
    //We draw the map list
    drawMapList(mapVector);
    //we draw the names
    drawText(mapVector, map_names_rects);
    handleMapSelection(mapVector, map_rects);

    return EXIT_SUCCESS;
}

void Song_selection_menu::drawMapList(std::vector<Map> mapVector) {
    SDL_Color white = {255, 255, 255};
    // for each map in the mapVector vector, we first create a rect, then we draw the name and the creator
    short number_of_maps = mapVector.size();
    std::cout << "Drawing " << number_of_maps << " maps." << std::endl;
    short i = 0;
    int numberOfRows = 7;
    int numberOfColumns = 1;
    for (const Map& map : mapVector) {
        i++;
        // we create a Pannel for the map
        Pannel map_pannel;


        if(i < numberOfRows){
            map_pannel.setX(100);
            map_pannel.setY(100 + 100 * i);
        }
        else{
            map_pannel.setX(100 + map_pannel.getWidth() + WINDOW_WIDTH / 7);
            map_pannel.setY(100 + 100 * (i - numberOfRows + 1));
            numberOfColumns = 2;
        }
        map_pannel.setWidth(WINDOW_WIDTH / 7);
        map_pannel.setHeight(WINDOW_HEIGHT / 10);


        //we add the pannel to the vector
        pannelVector.push_back(map_pannel);

        //we draw the pannel
        map_pannel.render(renderer_song_selection_menu);



        //we create a rect for the name that will take half of the map_rect
        SDL_Rect name_rect;
        name_rect.x = map_pannel.getX();
        name_rect.y = map_pannel.getY();
        name_rect.w = map_pannel.getWidth() / 2;
        name_rect.h = map_pannel.getHeight() / 2;
        std::cout << "Name rect added in the vector." <<std::endl;  
        //we push the name rect in the map_names_rects vector
        map_names_rects.push_back(name_rect);

            //infos about the map
        //we calculate the difficulty of the map
        mapVector[i-1].difficulty = mapVector[i-1].calculateDifficulty();
    }
    //for debugging purposes, we print the length of the map_rects vector
    std::cout << "map_rects vector length: " << map_rects.size() << std::endl;
    //we call the handleMapSelection function now that the map_rects vector is filled
    SDL_RenderPresent(renderer_song_selection_menu);
}


void Song_selection_menu::handleMapSelection(std::vector<Map> mapVector, std::vector<SDL_Rect> map_rects) {
    // Create a variable to store the selected map index
    int selectedMapIndex = -1;
    
    // We create a boolean that will be true until the user closes the menu
    bool quit = false;
    // We create an event handler
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // If the user clicks on the close button, we close the menu
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // If the user clicks on one of the map rects
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                // Check if the click is within any of the PannelVector 
                for (int i = 0; i < pannelVector.size(); i++) {
                    if (mouseX >= pannelVector[i].getX() && mouseX <= pannelVector[i].getX() + pannelVector[i].getWidth() && mouseY >= pannelVector[i].getY() && mouseY <= pannelVector[i].getY() + pannelVector[i].getHeight()) {
                        selectedMapIndex = i;
                        break;
                    }
                }

                // Break out of the event loop if a map is selected
                if (selectedMapIndex != -1) {
                    quit = true;
                    break;
                }
            }
        }
    }

    // Print the selected map index (1-indexed) if a map is selected
    if (selectedMapIndex != -1) {
        std::cout << "You chose level " << selectedMapIndex + 1 << std::endl;
        std::cout << "The name of the map is " << mapVector[selectedMapIndex].name << std::endl;
        std::cout << "The creator of the map is " << mapVector[selectedMapIndex].creator << std::endl;
        std::cout << "The BPM of the map is " << mapVector[selectedMapIndex].bpm << std::endl;
        //we start the game:
        Game game(mapVector[selectedMapIndex]);
    }
}
//the drawText function takes a vector of maps and a vector of rects as parameters, and draws the name and the creator of each map in the mapVector
void Song_selection_menu::drawText(std::vector<Map> mapVector, std::vector<SDL_Rect> map_names_rects) {
    //we create a color
    SDL_Color white = {255, 255, 255};
    
    //WE CHECK IF THE FONT FONT IS LOADED
    if (font == NULL) {
        std::cout << "Font font not loaded." << std::endl;
    } else {
        std::cout << "Font font loaded." << std::endl;
    }

   //we use the fontssm font.
   for (unsigned int i = 0; i < mapVector.size(); i++) {
        //we create a surface for the name
        SDL_Surface* name_surface = TTF_RenderText_Solid(font, mapVector[i].name.c_str(), white);
        //we create a texture for the name
        SDL_Texture* name_texture = SDL_CreateTextureFromSurface(renderer_song_selection_menu, name_surface);
        //we create a rect for the name
        SDL_Rect name_rect_to_write;
        name_rect_to_write.x = map_names_rects[i].x + 10;
        name_rect_to_write.y = map_names_rects[i].y + 10;
        name_rect_to_write.w = map_names_rects[i].w;
        name_rect_to_write.h = map_names_rects[i].h;
        //we draw the name
        SDL_RenderCopy(renderer_song_selection_menu, name_texture, NULL, &name_rect_to_write);
        std::cout << "Name of map " << i << " drawn." << "ie: " << mapVector[i].name << std::endl;

        //we create a surface for the creator
        SDL_Surface* creator_surface = TTF_RenderText_Solid(font, mapVector[i].creator.c_str(), white);
        //we create a texture for the creator
        SDL_Texture* creator_texture = SDL_CreateTextureFromSurface(renderer_song_selection_menu, creator_surface);
        //we create a rect for the creator, below the name_rect
        SDL_Rect creator_rect;
        creator_rect.x = map_names_rects[i].x + map_names_rects[i].w;
        creator_rect.y = map_names_rects[i].y + name_rect_to_write.w / 2 - 10;
        creator_rect.w = map_names_rects[i].w;
        creator_rect.h = map_names_rects[i].h;
        //we draw the creator
        SDL_RenderCopy(renderer_song_selection_menu, creator_texture, NULL, &creator_rect);
        std::cout << "Creator of map " << i << " drawn." << "ie: " << mapVector[i].creator << std::endl;


        //We create a string for the difficulty number
        std::string difficulty_string = "Difficulty: " + std::to_string(mapVector[i].calculateDifficulty());
        //we convert the string to a char*
        const char* difficulty_char = difficulty_string.c_str();

        //we create a surface for the difficulty
        SDL_Surface* difficulty_surface = TTF_RenderText_Solid(font, difficulty_char, white);
        //we create a texture for the difficulty
        SDL_Texture* difficulty_texture = SDL_CreateTextureFromSurface(renderer_song_selection_menu, difficulty_surface);
        //we create a rect for the difficulty, below the name_rect
        SDL_Rect difficulty_rect;
        difficulty_rect.x = map_names_rects[i].x + 10;
        difficulty_rect.y = map_names_rects[i].y + name_rect_to_write.w / 2 - 10;
        difficulty_rect.w = map_names_rects[i].w / 2;
        difficulty_rect.h = map_names_rects[i].h / 2;
        //we draw the difficulty
        SDL_RenderCopy(renderer_song_selection_menu, difficulty_texture, NULL, &difficulty_rect);
        std::cout << "Difficulty of map " << i << " drawn." << "ie: " << mapVector[i].calculateDifficulty() << std::endl;
        
    }
    SDL_RenderPresent(renderer_song_selection_menu);
}