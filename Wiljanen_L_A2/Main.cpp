// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A2 Not So Super Mario Bros

/*
The Main class takes in the input file through command line argument and puts the data into an array
The main class then uses that array in creating the mario object and then creates the game and runs the simulation
*/

#include <iostream>
#include <fstream>
#include "Game.h"

int main(int argc, char* argv[]){
    
    int arr[8];     //make an array to store the values from the file
    std::ifstream inFile(argv[1]);

    if (inFile.is_open()){
        for (int i = 0; i < 8; i++){
            inFile >> arr[i];           //add vales from the file into each position into the array respectfully
        }
    } else {
        std::cout << "Couldnt open file";
    }
    inFile.close(); //close file

    

    Mario mario(0,0,arr[2],0);  
    Game g(mario,arr);
    g.makeLevels();
    g.play();

    return 0;
}
