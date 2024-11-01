// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

/*
The Game class has all of the logic for setting up each level in an array of levels
It also moves the mario object around the grid for each level, and has all the logic
for running the simulation including:
    marios interactions with each character and outputting that to the poutput file
    outputting the grid and marios member variables to the output file
    when mario wins/loses the game
*/


#include <iostream>
#include <fstream>
#include <ctime>
#include "Game.h"
#include <fstream>

Game::Game(){}

Game::Game(Mario marioObj, int percentagesArr[]){
    
    mario = marioObj;
    
    for (int i = 0; i < 8; i++){        //copy over values into new class array
        percentages[i] = percentagesArr[i];
    }
    numLevels = percentages[0]; //get the number of levels given at running time
    dimesnsions = percentages[1];   //get dimensions of each level grid for move method
    simulation = new Level*[percentages[0]];  //array of levels

    std::srand(static_cast<unsigned>(std::time(0)));
}

Game::~Game(){
    delete[] simulation;
}

void Game::makeLevels(){
    for (int i = 0; i < numLevels; i++){
        simulation[i] = new Level(i, percentages);
    }
}

std::string Game::move(){
    std::string direction = "";
    int randMove = std::rand() % 4; //random number beteen 0 and 3
    
    //logic for moving mario on the grid
    switch (randMove){
        case 0: //move up
            if (mario.getRow() == 0){
                mario.setRow(dimesnsions-1);
            } else {
                mario.setRow(mario.getRow() - 1);
            }
            direction = "UP";
            break;
        case 1: //move down
            if (mario.getRow() == dimesnsions-1){
                mario.setRow(0);
            } else {
                mario.setRow(mario.getRow() + 1);
            }
            direction = "DOWN";
            break;
        case 2: //move right
            if (mario.getCol() == dimesnsions-1){
                mario.setCol(0);
            } else {
                mario.setCol(mario.getCol() + 1);
            }
            direction = "RIGHT";
            break;
        case 3: //move left
            if (mario.getCol() == 0){
                mario.setCol(dimesnsions-1);
            } else {
                mario.setCol(mario.getCol() -1);
            }
            direction = "LEFT";
            break;
    }
    return direction;

}

void Game::play(){

    std::ofstream outFile("gameLog.txt");   //output file for simulation

    int randStartingRow = std::rand() % dimesnsions;    //random starting location for mario
    int randStartingCol = std::rand() % dimesnsions;
    int defeatedEnemies = 0;

    mario.setRow(randStartingRow);  //set the row and col for marios starting position
    mario.setCol(randStartingCol);

    int currentLevel = 0;   //keep track of level marrio is one

    simulation[currentLevel]->fillGrid();   //create the level grid for the specific level

    outFile << simulation[currentLevel]->printGrid() << std::endl;

    
    std::string marioPosition = "Mario is starting at position: (" + std::to_string(mario.getRow()) + "," + std::to_string(mario.getCol()) + ") \n=========\n";
    outFile << marioPosition;
    
    char charAtPosition = ' ';
    std::string direction = "";
    
    std::string encounterType = "";

    std::string outputStatement = "";    //the string that tells about what mario encountered and all the information about him
    int l = 0;  
    bool hasWon = false;
    while (mario.getLives() != 0 && hasWon == false){
        
        charAtPosition = simulation[currentLevel]->getCharAtPosition(mario.getRow(), mario.getCol());
        marioPosition = "Mario is at position: (" + std::to_string(mario.getRow()) + "," + std::to_string(mario.getCol()) + ") ";
        simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(),'H');

        outFile << simulation[currentLevel]->printGrid();

        if (l == 0){    //conditional that will only run once. Used to change Marios starting character back onto the grid if necessary
            simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), charAtPosition);
        }
        l = 1;

        //implementation about moves and all that that will be outputted to file
        int goombaChance = std::rand() % 10;    //create a random number between 1 and 9
        int koopaChance = std::rand() % 100;
        int lvl = currentLevel;
        int bossChance = std::rand() % 2;

        std::string battleResult = "";

        switch(charAtPosition){ //logic for when mario moves to a new position and interacts with the object at the position
            case 'x':   //nothing
                encounterType = "Mario visited an empty space";
                simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');
                break;

            case 'm':   //mushroom
                encounterType = "Mario ate a mushroom";
                if (mario.getPowerLevel() < 2){
                    mario.setPowerLevel(mario.getPowerLevel() + 1);
                }
                simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');  //change the spot of the mushroom to contain nothing
                //comment to file
                break;

            case 'c':   //coin
                encounterType = "Mario collected a coin";
                mario.setCoins(mario.getCoins() + 1);
                simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');
                break;

            case 'g':   //goomba
                encounterType = "Mario encountered a goomba and ";
                if (goombaChance > 1){  //mario beats enemy
                    defeatedEnemies++;
                    battleResult = "won";
                    simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');
                    
                } else {
                    battleResult = "lost";
                    simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'g');
                    if (mario.getPowerLevel() > 0){
                        mario.setPowerLevel(mario.getPowerLevel()-1);
                        
                    } else {
                        mario.setLives(mario.getLives()-1);
                        defeatedEnemies = 0;
                    }
                }
                break;
                

            case 'k':   //koopa
                encounterType = "Mario encountered a koopa and ";
                if (koopaChance > 34){
                    defeatedEnemies++;
                    battleResult = "won";
                    simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');
                } else {
                    battleResult = "lost";
                    simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'k');
                    if (mario.getPowerLevel() > 0){
                        mario.setPowerLevel(mario.getPowerLevel()-1);
                    } else {
                        mario.setLives(mario.getLives()-1);
                        defeatedEnemies = 0;
                    }
                }
                break;
               

            case 'b':   //boss
                encounterType = "Mario encountered the boss and ";
                while (mario.getLives() > 0 && lvl == currentLevel && hasWon == false){
                    bossChance = std::rand() % 2;
                    if (bossChance > 0){
                        battleResult = "won";
                        simulation[currentLevel]->changeGrid(mario.getRow(), mario.getCol(), 'x');
                        if (currentLevel == numLevels-1){
                            outputStatement = "Level: " + std::to_string(currentLevel) + ". " + marioPosition + "Mario is at power level: " + 
                            std::to_string(mario.getPowerLevel()) + ". " + encounterType + battleResult + ". " + "Mario has " + std::to_string(mario.getLives()) + 
                            " lives left. Mario has " + std::to_string(mario.getCoins()) + " coins. " + "\n=========\n";
                            outFile << outputStatement;
                            outFile << "Mario has saved the princess";
                            hasWon = true;
                            
                        } else {
                            currentLevel++;
                            simulation[currentLevel]->fillGrid();
                            randStartingRow = std::rand() % dimesnsions;    //reset mario at a new location on the new level grid
                            randStartingCol = std::rand() % dimesnsions;
                            mario.setRow(randStartingRow); 
                            mario.setCol(randStartingCol);
                        }
                    } else {
                        battleResult = "lost";
                        if (mario.getPowerLevel() == 2){
                            mario.setPowerLevel(0);
                        } else {
                            mario.setLives(mario.getLives()-1);
                            defeatedEnemies = 0;
                        }
                    }
                }
                break;
                

            case 'w':   //warp pipe
                encounterType = "Mario has found a warp pipe and will move to the next level";
                currentLevel++;
                simulation[currentLevel]->fillGrid();
                randStartingRow = std::rand() % dimesnsions;    //reset mario at a new location on the new level grid
                randStartingCol = std::rand() % dimesnsions;
                mario.setRow(randStartingRow); 
                mario.setCol(randStartingCol);
                break;

            default:
                break;
        }
        if (defeatedEnemies == 7){  //mario gets an extra life if he defeats 7 enemies on the same life
            mario.setLives(mario.getLives() + 1);
            defeatedEnemies = 0;
        }
        if (mario.getCoins() == 20){    //mario gets an extra life if he collects 20 coins
            mario.setLives(mario.getLives() + 1);
            mario.setCoins(0);
        }
        if (hasWon){
            break;
        }
        if (encounterType == "Mario encountered the boss and " && battleResult == "lost"){
                    direction = "STAY PUT";
                } else {
                    direction = move(); //moves mario in a random direction and keeps track of the direction
                }
                outputStatement = "Level: " + std::to_string(currentLevel) + ". " + marioPosition + "Mario is at power level: " + 
                std::to_string(mario.getPowerLevel()) + ". " + encounterType + battleResult + ". " + "Mario has " + std::to_string(mario.getLives()) + 
                " lives left. Mario has " + std::to_string(mario.getCoins()) + " coins. " + "Mario will move " + direction + "\n=========\n";
                outFile << outputStatement;
        
        if (mario.getLives() == 0){
            outFile << "\nMario has died. Game is lost :(";
        }
        
    }


    
    delete[] simulation;
}


