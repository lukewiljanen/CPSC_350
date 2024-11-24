// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

/*
Handles input/output operations and the setup of the tournament.
runTournament() method in this class to initiate the tournament. This method 
will be called from main with parameters specifying the tournament format, input file, and 
output file
*/

#ifndef RUNSCAREGAMES_H
#define RUNSCAREGAMES_H
#include <iostream>
#include "Monster.h"
#include "TournamentTree.h"


class RunScareGames{
private:
    TournamentTree<Monster>* m_tournamentTree;  //pointer to the tournament tree
    int m_tournamentFormat; //tournament format (1 for single elimination, 2 for double elimination)
public:
    RunScareGames(int tournamentFormat);   //constructor takes in number of monsters and tournament format
    ~RunScareGames();   //destructor
    void runTournament(std::string inputFile, std::string outputFile);  //runs the tournament, takes in input and output files
};

#endif
