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

    //we stock the number of notes in the map
    int numberOfNotes = 0;

    //we create a vector of positions of the notes
    std::vector<int> notes_positions;
    // we read the file line by line and we push the values into the vector
    while (std::getline(file, line))
    {   
        numberOfNotes++;
        //we create the note
        int note = std::stoi(line);
        //we push the note into the vector
        notes_positions.push_back(note);
        lastNotePosition = note;
    }
    std::cout << "last note position: " << lastNotePosition << std::endl;

    //we using the number of notes and the last note position, we calculate the average bpm
    int averageBpm = (lastNotePosition / numberOfNotes) * 2;

    //we calculate the difficulty by multiplying the average bpm by the number of notes
    difficulty = averageBpm * numberOfNotes / 10;

    std::cout << "Number of notes: " << notes_positions.size() << std::endl;
    std::cout << "Average bpm: " << averageBpm << std::endl;
    std::cout << "Difficulty: " << difficulty << std::endl;
    return difficulty;
}


