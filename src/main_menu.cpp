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


    

    if (background_texture == nullptr)
    {
        std::cout << "Background could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (open_editor_texture == nullptr)
    {
        std::cout << "open_editor_texture could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (open_game_texture == nullptr)
    {
        std::cout << "open_game_texture could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // we place the button to open the editor
    open_editor_rect.x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
    open_editor_rect.y = WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2;
    open_editor_rect.w = 0; // Initially set the width to 0
    open_editor_rect.h = BUTTON_HEIGHT;

    // we place the button to open the game
    open_game_rect.x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
    open_game_rect.y = WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 150;
    open_game_rect.w = 0; // Initially set the width to 0
    open_game_rect.h = BUTTON_HEIGHT;

    
    //we set the pos and size of the pannel
    pannel1.setPosition(100, 200);
    pannel1.setWidth(200);
    pannel1.setHeight(200);
    
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
            // if the user clicks on the button to open the editor
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= open_editor_rect.x && e.button.x <= open_editor_rect.x + open_editor_rect.w && e.button.y >= open_editor_rect.y && e.button.y <= open_editor_rect.y + open_editor_rect.h)
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
            // if the user clicks on the button to open the game
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= open_game_rect.x && e.button.x <= open_game_rect.x + open_game_rect.w && e.button.y >= open_game_rect.y && e.button.y <= open_game_rect.y + open_game_rect.h)
            {
                // we quit the menu
                quit = true;
                // we launch the Song_selection_menu
                std::cout << "Launching the Song_selection_menu." << std::endl;
                Song_selection_menu song_selection_menu;
                // we destroy the menu
                Main_menu::~Main_menu();
            }
            // if the user clicks on the white square in the middle
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= WINDOW_WIDTH / 2 - WHITE_SQUARE_SIZE / 2 && e.button.x <= WINDOW_WIDTH / 2 + WHITE_SQUARE_SIZE / 2 && e.button.y >= WINDOW_HEIGHT / 2 - WHITE_SQUARE_SIZE / 2 && e.button.y <= WINDOW_HEIGHT / 2 + WHITE_SQUARE_SIZE / 2)
            {
                // Start the animation to reveal the buttons
                if (!buttonsVisible)
                {
                    buttonsVisible = true;
                    animationStartTime = SDL_GetTicks();
                }
                //we use an animation on the pannel
                std::cout << "Moving the pannel." << std::endl;
                
                //Animations::resizePannel(pannel1, 700, 600, 1000, renderer_menu);
                //we apply an image to the pannel
                pannel1.applyImage(renderer_menu, "assets/menu/chatsalade.jpg");
    
            }
        }

        // we clear the renderer
        SDL_RenderClear(renderer_menu);
        // we render the background
        SDL_RenderCopy(renderer_menu, background_texture, NULL, NULL);
        //we render the pannel
        pannel1.render(renderer_menu);
        

        if (buttonsVisible)
        {
            // Calculate the current width of the buttons based on the animation progress
            int currentTime = SDL_GetTicks();
            int elapsedTime = currentTime - animationStartTime;
            float animationProgress = (float)elapsedTime / ANIMATION_DURATION;
            int buttonWidth = static_cast<int>(BUTTON_WIDTH * animationProgress);

            // Limit the button width to the maximum width
            if (buttonWidth > BUTTON_WIDTH)
                buttonWidth = BUTTON_WIDTH;

            // Update the button widths
            open_editor_rect.w = buttonWidth;
            open_game_rect.w = buttonWidth;
        }
        else
        {
            //we render the white square in the middle
            SDL_SetRenderDrawColor(renderer_menu, 255, 255, 255, 255);
            SDL_Rect white_square_rect;
            white_square_rect.x = WINDOW_WIDTH / 2 - WHITE_SQUARE_SIZE / 2;
            white_square_rect.y = WINDOW_HEIGHT / 2 - WHITE_SQUARE_SIZE / 2;
            white_square_rect.w = WHITE_SQUARE_SIZE;
            white_square_rect.h = WHITE_SQUARE_SIZE;
            SDL_RenderFillRect(renderer_menu, &white_square_rect);
        }

        // we render the buttons
        SDL_RenderCopy(renderer_menu, open_editor_texture, NULL, &open_editor_rect);
        SDL_RenderCopy(renderer_menu, open_game_texture, NULL, &open_game_rect);


        // we update the screen
        SDL_RenderPresent(renderer_menu);
    }
    return 1;
}