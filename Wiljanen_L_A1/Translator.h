#pragma once
#include "Model.h"
#include <iostream>


class Translator{

public:

    Translator();   //default constructor
    ~Translator();  //default deconstructor

    std::string translateEnglishWord(std::string word);          //translates a single english word to Rövarspråket
    std::string translateEnglishSentence(std::string sentence); //translates an entire english sentence to Rövarspråket

};