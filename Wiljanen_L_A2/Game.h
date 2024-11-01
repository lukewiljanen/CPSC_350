// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Mario.h"
#include "Level.h"

class Game{
private:
    int numLevels;            //number of levels
    Level** simulation;      //array that holds all the levels
    int percentages[8];     //input file with all information about simulation
    std::string move();    //move marrio object
    int dimesnsions;
public:
    Game();
    Game(Mario, int[]); //mario object, and percentages array for levels
    ~Game();
    void play();        //method that runs the simulation
    void makeLevels(); //sets up the level with all the characters
    Mario mario;      //mario object
};
#endif

