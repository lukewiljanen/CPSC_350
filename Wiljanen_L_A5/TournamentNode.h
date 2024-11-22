// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

#ifndef TOURNAMENTNODE_H
#define TOURNAMENTNODE_H
#include <iostream>
#include "Monster.h"

/*
Represents a single match node within the tournament tree.
Attributes:
winner: A pointer to the competitor who won this match.
left and right pointers: These link to the child nodes, representing the competitors in this match.
This class will be for organizing and tracking each match within the tournament.
*/
template <typename T>
class TournamentNode{
private:
    

public:
    TournamentNode(Monster* winner);    //constructor that takes in a monster pointer
    ~TournamentNode();  //destructor
    Monster getMonster();   //returns the monster pointer

    //probably need to add more stuff here
    Monster* m_winner;
    TournamentNode<T>* m_left;
    TournamentNode<T>* m_right;

};

/*
Constructor initializes the winner to a monster object, and initalizes left and right pointers to null.
*/
template <typename T>
TournamentNode<T>::TournamentNode(Monster* winner){
    m_winner = winner;
    m_left = nullptr;
    m_right = nullptr;
}

/*
Destructor sets the left and right pointers to null
*/
template <typename T>
TournamentNode<T>::~TournamentNode(){
    m_left = nullptr;
    m_right = nullptr;
}

/*
Returns the monster pointer
*/
template <typename T>
Monster TournamentNode<T>::getMonster(){
    return *m_winner;
}


#endif
