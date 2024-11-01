#include "Model.h"
#include <iostream>


Model::Model(){}    

Model::~Model(){}

//takes a single consonant character as input and returns a string representing 
//its encoding in Rövarspråket. Capitalization should be preserved.
std::string Model::translateSingleConstonant(char constonant){
    
    std::string translation = "";       //conver the char to a string and add o's around it.
    translation += constonant;
    translation += "o";
    translation += constonant;

    return translation;
}

//translateSingleVowel – takes a single vowel character as input and returns a string representing 
//its encoding in Rövarspråket. Capitalization should be preserved.
std::string Model::translateSingleVowel(char vowel){
    
    std::string vowelTranslation = "";      //convert the char to a string
    vowelTranslation += vowel;

    return vowelTranslation;
}

//check to see if the character is a vowel or not; also checks to see if there is a special character which is treated the same as a vowel.
//returns true if it is a vowel/special char and false otherwise
//also accounts for uppercase letters.
bool Model::isVowel(char letter){
    switch (letter)
    {
    case 'a':
    case 'A':
        return true;
        break;
    case 'e':
    case 'E':
        return true;
        break;
    case 'i':
    case 'I':
        return true;
        break;
    case 'o':
    case 'O':
        return true;
        break;
    case 'u':
    case 'U':
        return true;
        break;
    case '.':
    case ',':
    case '?':
    case '!':
    case '/':
    case ':':
    case ';':
    case '-':
        return true;
        break;
    default:
        return false;
        break;
    }
}

