#pragma once
#include <iostream>


class Model{
    

public:
    
    Model();    //default constructor
    ~Model();   //default deconstructor

    std::string translateSingleConstonant(char constonant); //translates a single constonant to Rövarspråket
    std::string translateSingleVowel(char vowel);           //translates a single vowel to Rövarspråket
    bool isVowel(char letter);                              //checks to see if a char is a vowel or special character

}; 

