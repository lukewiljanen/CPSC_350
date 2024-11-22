// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

#include "RunScareGames.h"
#include <iostream>

int main (int argc, char** argv){

    if (argc != 3){
        return 0;
    }

    RunScareGames* games = new RunScareGames(8,1);
    games->runTournament(argv[1], argv[2]);

    delete games;
    
    return 0;
}
