// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A4 Genetic Palindromes

#include "DNASeq.h"
#include <iostream>

// constructor for a DNASeq object. Takes in a string and adds each character to the sequence.
DNASeq::DNASeq(std::string s)
{
    for (int i = 0; i < s.length(); i++){
        sequence.addBack(s[i]);
    }
}

// constructor for a DNASeq object. Takes in a DblList of characters and adds each character to the sequence.
DNASeq::DNASeq(DblList<char> s){
    sequence = s;
}

// default constructor for a DNASeq object.
DNASeq::DNASeq(){}

// destructor for a DNASeq object.
DNASeq::~DNASeq()
{
}

// returns the complement of the DNA sequence.
// if the sequence is not valid (contains a letter other than A, T, C, or G), returns an empty DblList.
DblList<char> DNASeq::complement(){
    DblList<char> comp;
   for(int i = 0; i < sequence.size(); i++){
        if(sequence.get(i) == 'A'){
            comp.addFront('T');
        }else if(sequence.get(i) == 'T'){
            comp.addFront('A');
        }else if(sequence.get(i) == 'C'){
            comp.addFront('G');
        }else if(sequence.get(i) == 'G'){
            comp.addFront('C');
        } else { // if not A, T, C, or G
            DblList<char> empty;
            return empty;
        }
    }
    return comp;
}

// takes in a start and end index and returns a substring of the DNA sequence from start(s) to end(e).
DblList<char> DNASeq::substring(int s, int e){
    DblList<char> sub;
    for(int i = s; i <= e; i++){
        sub.addBack(sequence.get(i));
    }
    return sub;
}

// returns true if the DNA sequence is a genetic palindrome, false otherwise.
bool DNASeq::isGeneticPalindrome(){
    DblList<char> comp = complement();
    if (comp.isEmpty()){
        return false; 
    }
    for(int i = 0; i < sequence.size(); i++){
        if(sequence.get(i) != comp.get(i)){
            return false;
        }
    }
    return true;
}

// returns the type of palindrome (if any) in the DNA sequence.
std::string DNASeq::palindromeDeterminer(){
    DblList<char> comp = complement();
    if(comp.isEmpty()){
        return "INVALID";
    } else if (isGeneticPalindrome()){
        return "Genetic Palindrome";
    } else {
        return "Not a Genetic Palindrome";
    }
}

// returns a string representation of the DNA sequence.
std::string DNASeq::toString(){
    std::string s;
    for(int i = 0; i < sequence.size(); i++){
        s += sequence.get(i);
    }
    return s;
}

// returns the size of the DNA sequence.
int DNASeq::size(){
    return sequence.size();
}
