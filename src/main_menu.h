#ifndef main_menu_H
#define main_menu_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Main_menu {
    public:

    //constructor
    Main_menu();
    //desctructor
    ~Main_menu();

    //the window that will contain the menu
    SDL_Rect window_menu_rect;
    //the rect that will act as a button to open the editor
    SDL_Rect open_editor_rect;
    //the rect that will act as a button to open the game
    SDL_Rect open_game_rect;

    //we define the size of the button
    int BUTTON_WIDTH = 200;
    int BUTTON_HEIGHT = 100;

    //we create a renderer for the menu 
    SDL_Renderer* renderer_menu = NULL;
    //we create a window for the menu
    SDL_Window* window_menu = NULL;

    //we define the size of the window
    int WINDOW_WIDTH = 1920;
    int WINDOW_HEIGHT = 1080;

    private:
    //methods
    //method to initialize the menu
    int init();
    //method that will loop until the user closes the menu, handling events
    int menuLoop();
    //textures
    SDL_Texture* background_texture = NULL;
    SDL_Texture* open_editor_texture = NULL;
    SDL_Texture* open_game_texture = NULL;
    //surfaces
    SDL_Surface* open_editor_surface = NULL;
    SDL_Surface* open_game_surface = NULL;
    

};

#endif // main_menu_H

