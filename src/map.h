#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Map {
    public:
        //infos about the map
        std::string name;
        std::string creator;

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



    private:

};
       
#endif // MAP_H
