// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A5 Scare Games

/*
TournamentTree class:
This class serves as the foundation for the tournament structure. It contain methods for inserting competitors,
playing matches, and managing the tournament tree.
*/

#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H

#include "TournamentNode.h"
#include "Monster.h"
#include <iostream>
#include <fstream>
#include <queue>


template <typename T>
class TournamentTree{
private:
    TournamentNode<T>* m_root;  // Root of the tournament tree
    void destroyTree(TournamentNode<T>* node);  //helper methods for deconstructor
    
    
    void insertHelper(TournamentNode<T>*& node, Monster* winner, int currDepth);   //helper method for insert

    void matchHelper(TournamentNode<T>* node);  //helper method for each match between monsters

public:
    int m_leafNodes;   //number of leaf nodes in the tournament tree

    TournamentTree();   //default constructor
    void generateEmptyTree(int numLeafNodes);   //generates an empty tournament tree with given number of leaf nodes (competitors)
    ~TournamentTree();  //destructor
    void insert(Monster* winner);   //inserts a new competitor into the tournament tree at a leaf node
    void saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode);   //saves the tournament tree as a .dot file
    void saveTreeAsDotHelper(TournamentNode<T>* rootNode, std::ofstream& file, int& nodeID);    //helper method for saveTreeAsDot
    void singleElimination(std::string inputFile, std::string outputFile);    //runs a single elimination tournament
    void doubleElimination(std::string inputFile, std::string outputFile);    //runs a double elimination tournament
}; 

/*
Constructor sets the root node to NULL
*/
template <typename T>
TournamentTree<T>::TournamentTree(){
    m_root = NULL;
}

/*
deconstructor uses a helper method to delete all nodes in the tree
*/
template <typename T>
TournamentTree<T>::~TournamentTree(){
    destroyTree(m_root);
}

/*
helper method for deconstructor that calls itself recursively to delete all nodes in the tree
checks if the node is null, if it is, it returns. Otherwise, it calls itself recursively on the left and right children
of the current node, and then deletes the current node
*/
template <typename T>
void TournamentTree<T>::destroyTree(TournamentNode<T>* node){
    if (node != NULL){
        destroyTree(node->m_left);
        destroyTree(node->m_right);
        delete node;
    }
}

/*
Inserts a new competitor into the tournament tree at a leaf node using the insertHelper method
takes in a monster pointer as a parameter
*/
template <typename T>
void TournamentTree<T>::insert(Monster* winner){
    insertHelper(m_root, winner, 0);
}

/*
Helper method for insert that takes in a node pointer and a monster pointer as parameters
fills in all of the leaf nodes of the tree with the given monster pointer
*/
template <typename T>
void TournamentTree<T>::insertHelper(TournamentNode<T>*& node, Monster* winner, int currDepth){
    if (node == NULL && currDepth == ((m_leafNodes / 2) - 1)){
        node = new TournamentNode<T>(winner);
        return;
    }
    if (node->m_left == NULL && currDepth + 1 == ((m_leafNodes / 2) - 1)){
        node->m_left = new TournamentNode<T>(winner);
    } else if (node->m_right == NULL && currDepth + 1 == ((m_leafNodes / 2) - 1)){
        node->m_right = new TournamentNode<T>(winner);
    } else {
        insertHelper(node->m_left, winner, currDepth + 1);
        insertHelper(node->m_right, winner, currDepth + 1);
    }
}

/*
method that generates an empty tournament tree with a given number of leaf nodes
if the number of  leaf nodes is odd, it decrements the number of leaf nodes by 1
creates a queue of nodes and pushes the root node onto the queue
continuously pops nodes off the queue and creates left and right children for each node
*/
template <typename T>
void TournamentTree<T>::generateEmptyTree(int numLeafNodes){

    m_leafNodes = numLeafNodes;

    //check to see if there is an even number of leaf nodes
    //if there is an odd number of leaf nodes decrement the number of leaf nodes by 1
    if (numLeafNodes % 2 != 0){
        numLeafNodes--;
    }

    std::queue<TournamentNode<T>*> q; //queue of tournament nodes
    
    m_root = new TournamentNode<T>(NULL);    //makes the root node a tournament node with a null pointer value
    
    q.push(m_root); //push the root node onto the queue
    
    int i = 1;  //counter
    while (i < ((numLeafNodes * 2) - 1)){
        //get the node in the front of the queue
        TournamentNode<T>* node = q.front();
        //pop the node off the queue
        q.pop();
        //create a left child
        TournamentNode<T>* left = new TournamentNode<T>(NULL);
        //create a right child
        TournamentNode<T>* right = new TournamentNode<T>(NULL);
        //set the left child of the node to the left child
        node->m_left = left;
        //set the right child of the node to the right child
        node->m_right = right;
        //push the left child onto the queue
        q.push(left);
        //push the right child onto the queue
        q.push(right);
        i+=2;   //increment the counter by 2 since there was 2 children created
    }
}


/*
You will use these methods in your code to save your winner and/ or loser bracket trees as DOT files
Then, you'll be able to visualize your trees at this link: https://dreampuf.github.io/GraphvizOnline/
*/

// Function to save the tree as a DOT file
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for DOT output: " << filename << "\n";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(rootNode, file, nodeID);
    file << "}\n";
    file.close();
}

// Recursive helper function for DOT file generation
template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) {
    if (node == NULL) return;

    int currentID = nodeID++;
    file << "    node" << currentID << " [label=\"" << node->m_winner->m_name
         << " (Power: " << node->m_winner->m_powerLevel << ")\"];\n";

    if (node->m_left) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->m_left, file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->m_right) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->m_right, file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
}

/*
method for a single elimination tournament format
takes in an input file and an output file
first an empty tournament tree is generated taking into consideration the number of leaf nodes
then the tree is filled with monsters based off of the input file. 
the match helper method is used to simulate the matches and determine the winner
the winner is then printed to the output file in the form of a dot file
*/
template <typename T>
void TournamentTree<T>::singleElimination(std::string inputFile, std::string outputFile){
    //read in the input file
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    TournamentTree<T>* tree = new TournamentTree<T>();
    tree->generateEmptyTree(m_leafNodes);


    //fills tree with monsters based off of input file
    if (input.is_open()){
        std::string line;
        while (getline(input, line)){
            std::string monsterName;
            int powerLevel;
            for (int i = 0; i < line.length(); i++){
                if (line[i] == ','){
                    std::string  powerLevelString = line.substr(i+2, line.length());
                    powerLevel = stoi(powerLevelString);
                    break;
                }
                monsterName += line[i];
            }
            
            Monster* monster = new Monster;
            monster->m_name = monsterName;
            monster->m_powerLevel = powerLevel;
            tree->insert(monster);
        }
        
    } else {
        std::cout << "Unable to open file" << inputFile << std::endl;
    }

    matchHelper(tree->m_root);

    //save the tree as a dot file
    saveTreeAsDot(outputFile, tree->m_root);


    input.close();


}

/*
method to help simulate the matches and determine the winner
takes in a tournament node and recursively calls itself on the left and right children until it reaches a leaf node
then it compares the power levels of the two monsters and determines the winner
the winner is then set as the winner of the node
*/
template <typename T>
void TournamentTree<T>::matchHelper(TournamentNode<T>* node){
    if (node == NULL){ //possibly flip this
        return;
    } 
    if (node->m_left == NULL && node->m_right == NULL){
        return;
    } else {
        matchHelper(node->m_left);
        matchHelper(node->m_right);
        Monster* winner1 = node->m_left->m_winner;
        Monster* winner2 = node->m_right->m_winner;
        Monster* winningMonster = (winner1->m_powerLevel > winner2->m_powerLevel) ? winner1 : winner2;
        node->m_winner = winningMonster;
    }
}

template <typename T>
void TournamentTree<T>::doubleElimination(std::string inputFile, std::string outputFile){
    //read in the input file
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    TournamentTree<T>* winnersBracket = new TournamentTree<T>();
    TournamentTree<T>* losersBracket = new TournamentTree<T>();
    winnersBracket->generateEmptyTree(m_leafNodes);
    losersBracket->generateEmptyTree(m_leafNodes-1);

    if (input.is_open()){
        std::string line;
        while (getline(input, line)){
            std::string monsterName;
            int powerLevel;
            for (int i = 0; i < line.length(); i++){
                if (line[i] == ','){
                    std::string  powerLevelString = line.substr(i+1, line.length());
                    powerLevel = stoi(powerLevelString);
                    break;
                }
                monsterName += line[i];
            }
            
            Monster* monster = new Monster;
            monster->m_name = monsterName;
            monster->m_powerLevel = powerLevel;
            winnersBracket->insert(monster);
        }
        
    } else {
        std::cout << "Unable to open file" << inputFile << std::endl;
    }

    input.close();
}



#endif
