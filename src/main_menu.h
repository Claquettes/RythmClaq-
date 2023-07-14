#ifndef main_menu_H
#define main_menu_H

#include <iostream>
#include <string>

#include "pannel.h"
#include "animations.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Main_menu {
public:
    // Constructor
    Main_menu();
    // Destructor
    ~Main_menu();

    // The window that will contain the menu
    SDL_Rect window_menu_rect;
    // The rect that will act as a button to open the editor
    SDL_Rect open_editor_rect;
    // The rect that will act as a button to open the game
    SDL_Rect open_game_rect;

    // We define the size of the button
    int BUTTON_WIDTH = 200;
    int BUTTON_HEIGHT = 100;

    // We create a renderer for the menu 
    SDL_Renderer* renderer_menu = NULL;
    // We create a window for the menu
    SDL_Window* window_menu = NULL;

    // We define the size of the window
    int WINDOW_WIDTH = 1920;
    int WINDOW_HEIGHT = 1080;

    //we create a pannel
    Pannel pannel1;
    

private:
    // Constants
    static const int WHITE_SQUARE_SIZE = 100; // Add this constant declaration

    // Methods
    // Method to initialize the menu
    int init();
    // Method that will loop until the user closes the menu, handling events
    int menuLoop();

    // Textures
    SDL_Texture* background_texture = NULL;
    SDL_Texture* open_editor_texture = NULL;
    SDL_Texture* open_game_texture = NULL;
    // Surfaces
    SDL_Surface* open_editor_surface = NULL;
    SDL_Surface* open_game_surface = NULL;

    //we create a vector of Pannel objects (for easier rendering)
    std::vector<Pannel> pannelVector; // Store the Pannel objects

    //we create a pannel for the editor button
    Pannel pannel_editor_button;
    //we create a pannel for the play button
    Pannel pannel_play_button;
    //we create a pannel for the quit button
    Pannel pannel_quit_button;

    void pannelInit();

};

#endif // main_menu_H
