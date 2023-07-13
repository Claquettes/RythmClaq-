#include "editor.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <fstream> //for file manipulation
#include "panel.h"
#include <cmath> //use to round numbers, useful for snapping notes to the grid
#include "saveWindow.h"

// constructor
Editor::Editor()
{
    std::cout << "Editor constructor called!" << std::endl;
    // we initialize the editor
    init();
}

// destructor
Editor::~Editor()
{
    std::cout << "Editor destructor called!" << std::endl;
    std::cout << "The temp_notes vector contains " << temp_notes.size() << " notes." << std::endl;
    // we free all of the textures and surfaces
    SDL_DestroyTexture(background_texture);
    // we close the editor window
    SDL_DestroyRenderer(renderer_editor);
    SDL_DestroyWindow(window_editor);
    // we quit SDL
    SDL_Quit();
}

int Editor::init()
{
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
    // we initialize SDL_image
    IMG_Init(IMG_INIT_PNG);
    
    // if everything is ok, we return 0 and we launch the menuLoop
    std::cout << "Menu initialized, calling editorLoop." << std::endl;
    editorLoop();
    return 0;
}

void Editor::editorLoop()
{
    std::cout << "editorLoop called!" << std::endl;
    // We create a boolean that will be true until the user closes the menu
    bool quit = false;
    // We create an event handler
    SDL_Event e;
    // We create a rect that will act as a test button


    // Create a back buffer for rendering off-screen
    SDL_Texture* backBuffer = SDL_CreateTexture(renderer_editor, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // If the user clicks on the test button, we close the menu
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= pannel_quit.getX() && e.button.x <= pannel_quit.getX() + pannel_quit.getWidth() && e.button.y >= pannel_quit.getY() && e.button.y <= pannel_quit.getY() + pannel_quit.getHeight())
            {
                quit = true;
            }
            // If the user clicks on the close button, we close the menu
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            //if the user clicks on the save button
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.button.x >= 0 && e.button.x <= WINDOW_WIDTH * 0.1 && e.button.y >= 0 && e.button.y <= WINDOW_HEIGHT * 0.1 - 10)
            {
                //we cout for debug
                std::cout << "Save button clicked!" << std::endl;
                //we call the saveWindow
                SaveWindow saveWindow(temp_notes);
            }
            else
            {
                // We handle the note placement
                Editor::handleNotePlacement(e);
            }
        }

        // Render to the back buffer
        SDL_SetRenderTarget(renderer_editor, backBuffer);
        SDL_SetRenderDrawColor(renderer_editor, 0, 0, 0, 255);
        SDL_RenderClear(renderer_editor);


        Editor::managePannels();
        

        // Every 32 pixels, we draw a line to symbolize a beat
        SDL_SetRenderDrawColor(renderer_editor, 0, 0, 0, 255);
        for (int i = 0; i < 5000; i += 32)
        {
            // We draw a thick white line every 4 beats, so every 128 pixels
            if (i % 128 == 0)
            {
                SDL_SetRenderDrawColor(renderer_editor, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer_editor, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.3);
                SDL_SetRenderDrawColor(renderer_editor, 0, 0, 0, 255);
            }
            else if (i % 64 == 0)
            {
                // We draw a yellow line every 2 beats, so every 64 pixels
                SDL_SetRenderDrawColor(renderer_editor, 255, 255, 0, 255);
                SDL_RenderDrawLine(renderer_editor, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.3);
                SDL_SetRenderDrawColor(renderer_editor, 0, 0, 0, 255);
            }
            else
            {
                SDL_RenderDrawLine(renderer_editor, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1, i + WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.3);
            }
        }

        // We draw the test button
        SDL_SetRenderDrawColor(renderer_editor, 223, 12, 78, 255);

        // Reset the render target to the default window
        SDL_SetRenderTarget(renderer_editor, nullptr);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer_editor, 0, 0, 0, 255);
        SDL_RenderClear(renderer_editor);

        // Copy the back buffer to the window for display
        SDL_RenderCopy(renderer_editor, backBuffer, nullptr, nullptr);

        // Render the notes on top of the scene
        Editor::renderNotes(temp_notes, renderer_editor);

        // Update the screen
        SDL_RenderPresent(renderer_editor);
    }

    // Clean up
    SDL_DestroyTexture(backBuffer);
}


int Editor::editorCli()
{
    std::cout << "Welcome to the RythmClaq editor!" << std::endl;

    std::cout << "What do you want to do?" << std::endl;
    std::cout << "1. Create a new map" << std::endl;
    std::cout << "2. Edit an existing map" << std::endl;
    // std::cout << "3. Delete a map" << std::endl;

    int choice;
    std::cin >> choice;
    // we need to define the variables here because of the switch, we can't define them in the cases
    std::string path;
    std::string map_name;
    std::string artist_name;
    std::string author_name;
    unsigned short bpm;

    switch (choice)
    {
    case 1:
        std::cout << "You chose to create a new map!" << std::endl;
        std::cout << "Lets create a new map!" << std::endl;
        std::cout << "What is the name of your map?" << std::endl;
        std::cin >> map_name;
        std::cout << "What is the name of the song's artist?" << std::endl;
        std::cin >> artist_name;
        std::cout << "What is your name?" << std::endl;
        std::cin >> author_name;
        std::cout << "What is the BPM of the song?" << std::endl;
        std::cin >> bpm;
        std::cout << "Nice, creating the map..." << std::endl;
        // we'll do the path of the map later.
        path = "path"; // default path for now
        createMap(map_name, artist_name, author_name, bpm, "path");
        break;
    case 2:
        std::cout << "You chose to edit an existing map!" << std::endl;
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }
}

// we define the createMap function

void Editor::createMap(std::string map_name, std::string artist_name, std::string author_name, unsigned short bpm, std::string path)
{

    // we generate the id of the map. We try with 1, if it already exists, we increment it by 1 until we find an id that doesn't exist
    int id = 1;
    // we check if a folder with the same name already exists
    while (std::filesystem::exists("maps/" + std::to_string(id)))
    {
        std::cout << "A map with the id " << id << " already exists, incrementing the id..." << std::endl;
        id++;
    }
    // Create a folder with the map name
    std::string command = "cd maps && mkdir " + std::to_string(id);
    system(command.c_str());

    // Create or open the info.txt file
    std::ofstream info_file("maps/" + std::to_string(id) + "/infos.txt");
    // Check if the file was successfully opened
    if (info_file.is_open())
    {
        // Write data to the file
        info_file << map_name << std::endl
                  << artist_name << std::endl
                  << author_name << std::endl
                  << bpm << std::endl;
        // Close the file
        info_file.close();
    }
    else
    {
        std::cout << "Something went wrong while creating the infos.txt file!" << std::endl;
    }
    // we create the .claq file
    std::ofstream claq_file("maps/" + std::to_string(id) + "/notes.claq");
    std::cout << "Map created!, Now lets place the notes!" << std::endl;
    unsigned int notepos = 0;
    std::cout << "Enter the position of the note (in px) (a beat is every 5px)" << std::endl;
    std::cout << "Enter -1 to stop" << std::endl;
    while (notepos != -1)
    {
        std::cin >> notepos;
        if (notepos != -1)
        {
            //we write the note position in the .claq file
            std::string note = std::to_string(notepos) + "\n";
            claq_file << notepos << std::endl;
        }
        else
        {
           break;
        }
    }

}

int Editor::editorGui()
{
    std::cout << "editorGui called!" << std::endl;
    return 0;
}

void Editor::handleNotePlacement(SDL_Event event)
{
    //if the event is a Left click, and that the coordinates are in the pannel_to_place_notes
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.x >= WINDOW_WIDTH * 0.1 && event.button.x <= WINDOW_WIDTH * 0.9 && event.button.y >= WINDOW_HEIGHT * 0.1 && event.button.y <= WINDOW_HEIGHT * 0.3)
    {
        // we get the position of the mouse
        int mouse_x = event.button.x;
        int mouse_y = event.button.y;
        // we get the position of the note
        int note_x = mouse_x - WINDOW_WIDTH * 0.1; // we substract the padding
        int note_y = mouse_y - WINDOW_HEIGHT * 0.1; // we substract the padding 

        // we get the position of the note in the temp_notes array
        int note_pos = Editor::snapToGrid(note_x) / 5;
        // we check if the note is already placed by going through the temp_notes array
        bool note_already_placed = false;
        for (int i = 0; i < temp_notes.size(); i++)
        {
            if (temp_notes[i] == note_pos)
            {
                note_already_placed = true;
            }
        }
        if (note_already_placed == false)
        {
            // we add the note to the temp_notes array
            temp_notes.push_back(note_pos);
            std::cout << "Note placed at " << note_pos << std::endl;
            //we place the note on the screen for visual feedback

            //we create a NEW panel using NEW
            Pannel *note_pannel = new Pannel();
            // we set the position of the pannel
            note_pannel->setX(note_pos * 5 + WINDOW_WIDTH * 0.1);
            note_pannel->setY(WINDOW_HEIGHT * 0.1);
            // we set the size of the pannel
            note_pannel->setSize(30, 30);
            // we set the color of the pannel
            note_pannel->setColor(noteColor);
            //we render the pannel
            note_pannel->render(renderer_editor);

        }
        else
        {
            std::cout << "Note already placed at " << note_pos << std::endl;
        }
    }
}

void Editor::renderNotes(std::vector<unsigned short> notes, SDL_Renderer* renderer)
{
    // we go through the notes array
    for (int i = 0; i < notes.size(); i++)
    {
        //we create a NEW panel using NEW
        Pannel* note_pannel = new Pannel();
        // we set the position of the pannel
        note_pannel->setX(notes[i] * 5 + WINDOW_WIDTH * 0.1);
        note_pannel->setY(WINDOW_HEIGHT * 0.1 - 10 + pannel_to_place_notes.getHeight() / 2);
        // we set the size of the pannel
        note_pannel->setSize(30, 30);
        // we set the color of the pannel
        note_pannel->setColor(noteColor);
        //we render the pannel
        note_pannel->render(renderer);
    }
}

int Editor::snapToGrid(int x)
{
    // We round the number to the nearest multiple of 32
    int rounded = round(static_cast<double>(x) / 32) * 32 - 15; // Subtract 15 to center the note
    return rounded;
}

void Editor::managePannels()
{
    SDL_Color pannel_to_place_notes_color = {255, 55, 25, 255};
        // We create a panel, which will be 5000px width of the screen width and 20% of the screen height
        pannel_to_place_notes.setPosition(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);
        pannel_to_place_notes.setSize(5000, WINDOW_HEIGHT * 0.2);
        pannel_to_place_notes.setColor(pannel_to_place_notes_color);
        pannel_to_place_notes.render(renderer_editor);

        // We draw the Header pannel
        SDL_Color pannel_header_color = {0, 0, 255, 255};
        pannel_header.setPosition(0, 0);
        pannel_header.setSize(WINDOW_WIDTH, WINDOW_HEIGHT * 0.1 - 10);
        pannel_header.setColor(pannel_header_color);
        pannel_header.render(renderer_editor);

        // We draw the save button, a pannel that takes 10% of the screen width and 100% of the header height
        SDL_Color pannel_save_color = {255, 255, 255, 255};
        pannel_save.setPosition(0, 0);
        pannel_save.setSize(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1 - 10);
        pannel_save.setColor(pannel_save_color);
        pannel_save.render(renderer_editor);

        // We draw the quit button, a pannel that takes 10% of the screen width and 100% of the header height
        SDL_Color pannel_quit_color = {110, 110, 110, 255};
        pannel_quit.setPosition(WINDOW_WIDTH * 0.9, 0);
        pannel_quit.setSize(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1 - 10);
        pannel_quit.setColor(pannel_quit_color);
        pannel_quit.render(renderer_editor);

}