// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A4 Genetic Palindromes

#ifndef PALINDROMEFINER_H
#define PALINDROMEFINER_H
#include <iostream>
#include "DNASeq.h"
#include "DblList.h"

// Finds all palindromes in a DNA sequence and prints them to the terminal.

class PalindromeFinder{

private:
public:
    PalindromeFinder();                 //Default constructor for a PalindromeFinder object.
    ~PalindromeFinder();                //Destructor for a PalindromeFinder object.
    void findPalindromes(DNASeq dna);   //Finds all palindromes in a DNA sequence and prints them to the terminal.

};

#endif
