// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

/*
The level class has all the logic for setting up each individual level full of characters
with the percent chance of each one given through the input file at run time
*/

#include <iostream>
#include "Level.h"
#include <ctime>

Level::Level(int number, int percentagesArr[]){
    levelNumber = number;
    
    for (int i = 0; i < 8; i++){        //copy over values into new class array
        percentages[i] = percentagesArr[i];
    }

    int dim = percentagesArr[1];    //dimension of the grid
    rows = dim;
    cols = dim;
    grid = new char*[dim];

    for (int i = 0; i < dim; i++){
        grid[i] = new char[dim];
    }

    pCoins = percentages[3];    // [3] Percent of coins
    pNothing = pCoins + percentages[4];  // [4] Percentage of nothing
    pGoombas = pNothing + percentages[5];  // [5] Percentage of goombas
    pCoopas = pGoombas + percentages[6];   // [6] Percentage of coopas
    pMushrooms = pCoopas + percentages[7];// [7] Percentage of mushrooms

    std::srand(static_cast<unsigned>(std::time(0)));
}

Level::Level()
{
}

Level::~Level(){
    for (int i = 0; i < rows; i++){
        delete[] grid[i];
    }
    delete[] grid;
}


// x - nothing
// m - a mushroom
// c - a coin
// g - a Goomba
// k - a Koopa Troopa
// b - the level boss
// w - a warp pipe

void Level::fillGrid(){
    
    int randR = std::rand() % rows;     //put the boss at a random place in the grid
    int randC = std::rand() % cols;
    grid[randR][randC] = 'b';

    if (levelNumber != percentages[0] - 1){     //check to see if it is the last level since there is not a warp pipe on final level
        while (grid[randR][randC] == 'b'){     //put the warp pipe at a random place in the grid that isnt the same as the boss      
            randR = std::rand() % rows; 
            randC = std::rand() % cols;
        }
        grid[randR][randC] = 'w';
    }
    
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int randPercent = std::rand() % 101; //generate random number between 0 and 100
            
            if (grid[i][j] == 'b' || grid[i][j] == 'w'){
                continue;
            }
            else if (randPercent < pCoins){
                grid[i][j] = 'c';
            }
            else if (randPercent > pCoins && randPercent < pNothing){
                grid[i][j] = 'x';
            }
            else if (randPercent > pNothing && randPercent < pGoombas){
                grid[i][j] = 'g';
            }
            else if (randPercent > pGoombas && randPercent < pCoopas){
                grid[i][j] = 'k';
            }
            else{
                grid[i][j] = 'm';
            }
            
        }
    }

}

std::string Level::printGrid(){
    std::string returnGrid = "";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            returnGrid += grid[i][j];
        }
        returnGrid += "\n";
    }
    returnGrid += "=========\n";
    return returnGrid;
}

void Level::changeGrid(int r, int c, char ch){
    grid[r][c] = ch;
}

char Level::getCharAtPosition(int r, int c){
    return grid[r][c];
}

