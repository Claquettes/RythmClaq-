#ifndef editor_H
#define editor_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> //not used yet

#include "pannel.h"
#include "animations.h"
#include "saveWindow.h"

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

    //we create a pannel to place the notes
    Pannel pannel_to_place_notes;

    //we crate a pannel for the header
    Pannel pannel_header;

    //we create a pannel to act as a save button
    Pannel pannel_save;
    
    //we create a pannel to act as the quit button
    Pannel pannel_quit;

    private:
    //initilization of the editor
    int init();
    //textures
    SDL_Texture* background_texture = NULL;
    //main loop of the editor
    void editorLoop();
    //method called if the user wants to create a new map using the cli
    int editorCli();
    //method called if the user wants to create a new map using the gui
    int editorGui();
    void createMap(std::string map_name, std::string artist_name, std::string creator_name, unsigned short bpm, std::string song_path);
    //method called if the user wants to place a note in the GUI
    void handleNotePlacement(SDL_Event event);

    //we create an array of unsigned short to store the notes
    std::vector<unsigned short> temp_notes;
    SDL_Color noteColor = {0, 255, 25, 255};
    //render all of the notes, by passing the array of notes positions and the renderer
    void renderNotes(std::vector<unsigned short> notes, SDL_Renderer* renderer);
    int snapToGrid(int x);

    TTF_Font* font;
    std::string map_name;


    //we create a method that manage the pannels
    void managePannels();
};

#endif // editor_H

