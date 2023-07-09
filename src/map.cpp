#include "map.h"
#include <iostream>
#include <string>
#include <vector>
#include <random> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Map::Map()
{
    std::cout << "Map constructor called!" << std::endl;

}

Map::~Map()
{
    std::cout << "Map destructor called!" << std::endl;
}


//function that calculates the difficulty of the map, by calculating the average of the bpm and the number of notes
int Map::calculateDifficulty()
{
    //we get the id of the map 
    unsigned int mapId = id;
    //we open the notes.claq file, located in the folder of the map
    std::ifstream file("maps/" + std::to_string(mapId) + "/notes.claq");
    std::string line;
    //we create a vector of positions of the notes
    std::vector<int> notes_positions;
    // we read the file line by line and we push the values into the vector
    while (std::getline(file, line))
    {
        //we create the note
        int note = std::stoi(line);
        //we push the note into the vector
        notes_positions.push_back(note);
    }
    std::cout << "Number of notes: " << notes_positions.size() << std::endl;
    return notes_positions.size();
}


