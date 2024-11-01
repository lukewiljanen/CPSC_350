// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Mario.h"

class Level{
private:
    int levelNumber; //level number
    int rows;   // grid dimesnsions
    int cols;   //^^
    char** grid;  // grid for the level
    int percentages[8]; //array that holds all the information given through input file as command line arg
    // [0] Number of lives
    // [1] Dimension of the grid
    // [2] Number of initial lives
    // [3] Percent of coins
    // [4] Percentage of nothing
    // [5] Percentage of goombas
    // [6] Percentage of coopas
    // [7] Percentage of mushrooms

    int pCoins;     //percent chance of a coin at each spot 
    int pNothing;   //percent chance of nothing at each spot 
    int pGoombas;   //percent chance of a goomba at each spot 
    int pCoopas;    //percent chance of a coopa at each spot 
    int pMushrooms; //percent chance of a mushroom at each spot 

public:
    Level(int, int[]);  //level number, percentages array
    Level();            
    ~Level();
    void fillGrid();    //fills the 2d array with characters considering their percentages
    std::string printGrid();    //prints the elements of the array
    void changeGrid(int,int,char);  //row, column, character that will be put at that index | changes character at index
    char getCharAtPosition(int,int);    //row, column | returns character at index
};

#endif

