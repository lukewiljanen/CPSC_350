// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A6 Spanning the Gamut

#include <iostream>
#include "WGraph.h"
#include <fstream>

int main (int argc, char** argv){

    if (argc != 2){
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    const std::string INPUT = argv[1];
    int numVertices;

    // Open the input file to get the number of vertices
    std::ifstream inFile(INPUT);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << INPUT << std::endl;
        return 1;
    }
    inFile >> numVertices;

    WGraph<double> g(numVertices);
    g.computeMST(INPUT);

    return 0;
}
