// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros
#ifndef MARIO_H
#define MARIO_H
#include <iostream>


class Mario
{
private:
    int coins;       // coins will be set to 0
    int lives;       //the amount of lives mario has
    int powerLevel;  //marios powerlevel
    int row;         //row at which mario is located
    int col;         //column at which mario is located
public:
    Mario(int, int, int, int); // lives and power level given through command line args
    Mario();
    ~Mario();

    //set up getters and setters
    int getRow();        //returns the row mario is at    
    void setRow(int);    //modifys the row where mario is at

    int getCol();        //returns the col mario is at
    void setCol(int);    //modifys the col where mario is at

    int getCoins();      //returns the number of coins mario has      
    void setCoins(int);  //modifys the number of coins mario has

    int getLives();      //returns the number of lives mario has
    void setLives(int);  //modifys the number of lives mario has

    int getPowerLevel();     //returns the power level mario has
    void setPowerLevel(int); //modifys the power level of mario


};

#endif


