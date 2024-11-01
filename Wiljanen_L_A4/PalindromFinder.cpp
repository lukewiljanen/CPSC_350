// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A4 Genetic Palindromes

#include "PalindromeFinder.h"
#include "DNASeq.h"
#include <iostream>

PalindromeFinder::PalindromeFinder(){}

PalindromeFinder::~PalindromeFinder(){}


//takes in a DNASeq object and finds all palindromes in the sequence.
//if the sequence is not valid (comp is empty), returns nothing and prints nothing.
//if the sequence is valid, identifies all substrings (of lengths greater than 4 and less than 
//the length of the sequence) of the DNA sequence which are themselves genetic palindromes.
//the substrings are printed from smallest length to largest length to the terminal.
void PalindromeFinder::findPalindromes(DNASeq dna){
    DblList<char> comp = dna.complement();
    if (comp.isEmpty()){
        return;
    }

    for (int i = 5; i < dna.size(); i++){
        for (int j = 0; j + i < dna.size(); j++){
            if (i - j < 5){
                continue;
            }
            DblList<char> sub = dna.substring(j, i);
            DNASeq sub2(sub);
            
            if (sub2.isGeneticPalindrome() && sub2.size() != dna.size()){
                std::cout << "\tSubstring " << sub2.toString() << " - Genetic Palindrome" << std::endl;
            }
        }
        
    }
}
