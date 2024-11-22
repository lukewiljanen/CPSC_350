// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

#include "Monster.h"
#include <iostream>


Monster::Monster(){}

Monster::Monster(std::string name, int powerLevel){
    m_name = name;
    m_powerLevel = powerLevel;
}

Monster::~Monster(){}

Monster Monster::compareMonsters(Monster* monster1, Monster* monster2){
    if(monster1->m_powerLevel > monster2->m_powerLevel){
        return *monster1;
    }
    else{
        return *monster2;
    }
}