#include "editor.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//constructor
Editor::Editor(){
    std::cout << "Editor constructor called!" << std::endl;
    //we initialize the editor
    init();
}

//destructor
Editor::~Editor(){
    std::cout << "Editor destructor called!" << std::endl;
    //we free all of the textures and surfaces
    SDL_DestroyTexture(background_texture);
    //we close the editor window
    SDL_DestroyRenderer(renderer_editor);
    SDL_DestroyWindow(window_editor);
    //we quit SDL
    SDL_Quit();
}

int Editor::init(){
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
    //we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);
    // we load the background image
    background_texture = IMG_LoadTexture(renderer_editor, "assets/menu/EDITORTEXTURE.png");
    // we render the background
    SDL_RenderCopy(renderer_editor, background_texture, NULL, NULL);
    // we update the screen
    SDL_RenderPresent(renderer_editor);
    

    if (background_texture  == nullptr)
    {
        std::cout << "Background could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling editorLoop." << std::endl;
    editorLoop();
    return 0;
}

void Editor::editorLoop(){
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

    //we draw the test button
    SDL_SetRenderDrawColor(renderer_editor, 223, 12, 78, 255);
    SDL_RenderFillRect(renderer_editor, &test_rect);
    SDL_RenderPresent(renderer_editor);

    //we listen to events, and we close the menu if the user clicks on the test button
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
