#ifndef SONG_SELECTION_MENU_H
#define SONG_SELECTION_MENU_H

#include "map.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Song_selection_menu {

    public:
    //constructor
    Song_selection_menu();
    //destructor
    ~Song_selection_menu();
    //we define the size of the window
    int WINDOW_WIDTH = 1920;
    int WINDOW_HEIGHT = 1080;

    //we create a renderer for the ssm
    SDL_Renderer* renderer_song_selection_menu = NULL;
    //we create a window for the ssm
    SDL_Window* window_song_selection_menu = NULL;

    //we create a vector of Map objects
    std::vector<Map> mapVector; // Store the Map objects

    TTF_Font* font;
    private:
    
    //function that scans the maps folder and adds the maps to the vector
    int refreshMapList();

    int init();
    //textures
    SDL_Texture* background_texture = NULL;
    //we create a function to loop the ssm
    void song_selection_menuLoop();
    //we create a function to draw the vector of maps, that takes the vector as an argument
    void drawMapList(std::vector<Map> mapVector);
    //we create a vector of map_rects
    std::vector<SDL_Rect> map_rects; 
    //void that will handle the map selection, and launch the game. 
    void handleMapSelection(std::vector<Map> mapVector,  std::vector<SDL_Rect> map_rects);
    
};

#endif // SONG_SELECTION_MENU_H

