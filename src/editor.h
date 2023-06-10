#ifndef editor_H
#define editor_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Editor {
    public:

    //constructor
    Editor();
    //destructor
    ~Editor();
    //we define the size of the window
    int WINDOW_WIDTH = 1300;
    int WINDOW_HEIGHT = 800;

    //we create a renderer for the editor
    SDL_Renderer* renderer_editor = NULL;
    //we create a window for the editor
    SDL_Window* window_editor = NULL;

    private:
    int init();
    //textures
    SDL_Texture* background_texture = NULL;
    void editorLoop();

};

#endif // editor_H

