// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

/*
Main method to run the tournament taking in an input file of competitors and and output file for the dot file output
*/

#include "RunScareGames.h"
#include <iostream>

int main (int argc, char** argv){

    if (argc != 3){
        std::cout << "Not enough arguments";
        return 0;
    }

    std::string inputFile = argv[1];    // monsters.txt file with all the monsters
    std::string tournamentType = argv[2];   // single or double tournament

    const std::string SINGLE_ELIMINATION_TOURNAMENT = "single";
    const std::string DOUBLE_ELIMINATION_TOURNAMENT = "double";

    if (tournamentType == SINGLE_ELIMINATION_TOURNAMENT){   //run single tournament
        RunScareGames* games = new RunScareGames(1);
        games->runTournament(inputFile, "output.txt");
        delete games;
    } else if (argv[2] == DOUBLE_ELIMINATION_TOURNAMENT){   //run double tournament
        RunScareGames* games = new RunScareGames(2);
        games->runTournament(inputFile, "output.txt");
        delete games;
    } else {
        std::cout << "Invalid tournament format";   //if the inputted tournament format is neither single nor double
    }
    
    return 0;
}
