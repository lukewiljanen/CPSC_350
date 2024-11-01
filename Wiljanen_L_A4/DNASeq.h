// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A4 Genetic Palindromes

#ifndef DNASEQ_H
#define DNASEQ_H
#include <iostream>
#include "DblList.h"


// Represents a DNA sequence as a doubly-linked list of characters.
// Provides methods to perform common operations on DNA sequences, such as
// finding the complement, extracting a substring, and determining if the
// sequence is a genetic palindrome.


class DNASeq{

private:
    DblList<char> sequence; ///< The DNA sequence stored as a doubly-linked list.
public:
    DNASeq();                           //Default constructor for a DNASeq object.
    DNASeq(std::string s);             //Overloaded constructor: constructs a DNASeq object from a string.
    DNASeq(DblList<char> s);          //Overloaded constructor: constructs a DNASeq object from a DblList of characters.
    ~DNASeq();                       //Destructor for a DNASeq object.
    DblList<char> complement();     //Returns the complement of the DNA sequence.
    DblList<char> substring(int s, int e);  //Returns a substring of the DNA sequence from start(s) to end(e).
    bool isGeneticPalindrome();             // Determines if the DNA sequence is a genetic palindrome.
    std::string palindromeDeterminer();     // Determines the type of palindrome (if any) in the DNA sequence.
    int size();                             // Returns the size of the DNA sequence.
    std::string toString();                 // Returns a string representation of the DNA sequence.

};

#endif
