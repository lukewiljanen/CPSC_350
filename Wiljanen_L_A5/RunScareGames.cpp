// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games


#include "RunScareGames.h"
#include "TournamentTree.h"
#include <iostream>
#include <fstream>
#include <string>

/*
Takes in the number of monsters and tournament format, and creates a new RunScareGames object.
*/
RunScareGames::RunScareGames(int numMonsters, int tournamentFormat){
    m_numMonsters = numMonsters;
    m_tournamentFormat = tournamentFormat;
    m_tournamentTree = new TournamentTree<Monster>();
}

/*
deletes the tournament tree
*/
RunScareGames::~RunScareGames(){
    delete m_tournamentTree;
}

/*
Runs the tournament, takes in input and output files
sets the number of leaf nodes in the tournament tree to the number of monsters in the input file
calls either the single elimination or double elimination method based on the tournament format
*/
void RunScareGames::runTournament(std::string inputFile, std::string outputFile){
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    m_tournamentTree->m_leafNodes = m_numMonsters;

    if (m_tournamentFormat == 1){
        m_tournamentTree->singleElimination(inputFile, outputFile);
    } else if (m_tournamentFormat == 2){
        m_tournamentTree->doubleElimination(inputFile, outputFile);
    } else {
        std::cout << "Invalid tournament format" << std::endl;
    }
    
}

