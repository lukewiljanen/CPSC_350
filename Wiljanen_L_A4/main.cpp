// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A4 Genetic Palindromes

#include <iostream>
#include <fstream>
#include "PalindromeFinder.h"

int main(int argc, char* argv[]){

    std::ifstream inFile;
    inFile.open(argv[1]);
    std::string line;
    PalindromeFinder p;
    while(getline(inFile, line)){
        if (line == "END"){
            break;
        }
        DNASeq dna(line);
        std::cout << line << " - " << dna.palindromeDeterminer() << std::endl;
        p.findPalindromes(dna);
    }
    inFile.close();
    return 0;
}
