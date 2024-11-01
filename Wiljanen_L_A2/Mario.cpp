// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

/*
The mario class sets up all of marios qualities and has setter and getter methods to
access and modify all of his qualities
*/


#include "Mario.h"
#include <iostream>


Mario::Mario(int r, int c, int givenLives, int givenPowerLevel){
    row = r;    
    col = c;    
    lives = givenLives;     
    powerLevel = givenPowerLevel;   
    coins = 0;                       // mario starts with 0 coins when the simulation begins

}

Mario::Mario(){}
Mario::~Mario(){}

//getter methods
int Mario::getRow(){
    return row;
}
int Mario::getCol(){
    return col;
}
int Mario::getCoins(){
    return coins;
}
int Mario::getLives(){
    return lives;
}
int Mario::getPowerLevel(){
    return powerLevel;
}

//setter methods
void Mario::setRow(int numb){
    row = numb;
}
void Mario::setCol(int numb){
    col = numb;
} 
void Mario::setCoins(int numb){
    coins = numb;
}
void Mario::setLives(int numb){
    lives = numb;
}
void Mario::setPowerLevel(int numb){
    powerLevel = numb;
}









