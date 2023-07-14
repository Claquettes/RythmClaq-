#include "main_menu.h"
#include "song_selection_menu.h"

#include "pannel.h"
#include "animations.h"

#include "editor.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Main_menu::Main_menu()
{
    std::cout << "Main_menu constructor called!" << std::endl;
    Main_menu::init();
}

Main_menu::~Main_menu()
{
    std::cout << "Main_menu destructor called!" << std::endl;
    // we free all of the textures and surfaces
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(open_editor_texture);
    SDL_DestroyTexture(open_game_texture);

    SDL_FreeSurface(open_game_surface);
    SDL_FreeSurface(open_editor_surface);

    // we close the menu window
    SDL_DestroyRenderer(renderer_menu);
    SDL_DestroyWindow(window_menu);
    // we quit SDL
    SDL_Quit();
}

int Main_menu::init()
{
    std::cout << "Main_menu init called!" << std::endl;
    // we initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the window
    window_menu = SDL_CreateWindow("RythmClaq", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_menu == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we create the renderer
    renderer_menu = SDL_CreateRenderer(window_menu, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_menu == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);
    // we load the background image
    background_texture = IMG_LoadTexture(renderer_menu, "assets/menu/howl.png"); // static for now, will be dynamic later
    
    //we initialize the pannels
    pannelInit();

    //we cout for debug
    std::cout << "pannel1 x: " << pannel1.getX() << std::endl;
    std::cout << "pannel1 y: " << pannel1.getY() << std::endl;
    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling menuLoop." << std::endl;
    menuLoop();
    return 0;
}

int Main_menu::menuLoop()
{
    std::cout << "Main_menu menuLoop called!" << std::endl;
    // we create a boolean that will be true until the user closes the menu
    bool quit = false;
    // we create an event handler
    SDL_Event e;

    const int ANIMATION_DURATION = 300; // Duration of the reveal animation in milliseconds
    int animationStartTime = 0;         // Start time of the animation
    bool buttonsVisible = false;        // Flag to track whether the buttons should be visible or hidden

    // we listen to events until the user closes the menu
    while (!quit)
    {
        // we poll the events
        while (SDL_PollEvent(&e) != 0)
        {
            // if the user closes the menu
            if (e.type == SDL_QUIT)
            {
                // we quit the menu
                quit = true;
            }
            // if the user clicks
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                // we get the mouse coordinates
                int x, y;
                SDL_GetMouseState(&x, &y);
                // we check if the mouse is inside the editor button
                if (pannel_editor_button.isInside(x, y))
                {
                    // we quit the menu
                    quit = true;
                    //we destroy the menu
                    Main_menu::~Main_menu();
                
                    // we launch the editor
                    std::cout << "Launching the editor." << std::endl;
                    Editor editor;
                    Main_menu::~Main_menu();
                }
                // we check if the mouse is inside the game button
                else if (pannel_play_button.isInside(x, y))
                {
                   // we quit the menu
                    quit = true;
                    // we launch the Song_selection_menu
                    std::cout << "Launching the Song_selection_menu." << std::endl;
                    Song_selection_menu song_selection_menu;
                    // we destroy the menu
                    Main_menu::~Main_menu();
                }
                //we check if the mouse is inside the quit button
                else if (pannel_quit_button.isInside(x, y))
                {
                    // we quit the menu
                    quit = true;
                    // we destroy the menu
                    Main_menu::~Main_menu();
                }
            }
        }
        // we clear the renderer
        SDL_RenderClear(renderer_menu);
        // we render the background
        SDL_RenderCopy(renderer_menu, background_texture, NULL, NULL);
        //we render the vector of pannels
        for (int i = 0; i < pannelVector.size(); i++) {
            pannelVector[i].render(renderer_menu);
        }
        
        // we update the screen
        SDL_RenderPresent(renderer_menu);
    }
    return 1;
}

void Main_menu::pannelInit() {
    //we place the pannel to open the editor
    pannel_editor_button.setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2);
    pannel_editor_button.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    pannel_editor_button.applyImage(renderer_menu, "assets/menu/EDITORTEXTURE.png");

    //we place the pannel to open the game
    pannel_play_button.setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 150);
    pannel_play_button.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    pannel_play_button.applyImage(renderer_menu, "assets/menu/PLAYTEXTURE.png");

    //we place the pannel to close the game
    pannel_quit_button.setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 300);
    pannel_quit_button.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);


    
    //we set the pos and size of the pannel
    pannel1.setPosition(100, 200);
    pannel1.setWidth(200);
    pannel1.setHeight(200);


    //we add these pannels to the vector
    pannelVector.push_back(pannel_editor_button);
    pannelVector.push_back(pannel_play_button);
    pannelVector.push_back(pannel1);
    pannelVector.push_back(pannel_quit_button);
}