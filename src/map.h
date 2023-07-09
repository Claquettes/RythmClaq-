#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>

class Map {
    public:
        //infos about the map
        std::string name;
        std::string creator;
        unsigned int id;
        //METHODS
        //constructor
        Map();
        //destructor
        ~Map();
        short difficulty;
        short bpm;
        //infos about the song
        std::string song_name;
        std::string artist_name;
        std::string song_path;

        int calculateDifficulty();
    private:
};
       
#endif // MAP_H
