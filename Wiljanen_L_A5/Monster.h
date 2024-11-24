// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

/*
Monster object that has a name and power level
*/

#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>


class Monster
{
private:
    
public:
    Monster();
    Monster(std::string name, int powerLevel);
    ~Monster();
    std::string m_name;
    int m_powerLevel;
    Monster compareMonsters(Monster* monster1, Monster* monster2);
};

#endif
