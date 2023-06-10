#ifndef SONG_SELECTION_MENU_H
#define SONG_SELECTION_MENU_H

#include "map.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    private:
    int refreshMapList();

 
    int init();
    //textures
    SDL_Texture* background_texture = NULL;
    void song_selection_menuLoop();


};

#endif // SONG_SELECTION_MENU_H

