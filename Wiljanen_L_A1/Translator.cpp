#include "Translator.h"
#include <iostream>


Translator::Translator(){}

Translator::~Translator(){}


// translateEnglishWord – takes a single string representing a single English word as input 
// and returns a string representing the Rövarspråket translation.
std::string Translator::translateEnglishWord(std::string word){
    
    std::string newWord = "";                                   // a string variable that will be returned after each translated char is added to it
    Model character;                                            // Model object that will be used to access the public methods of the Model class

    for (int i = 0; i < word.length(); i++){                    // loop through each char in the word
        
        if (character.isVowel(word[i])){                        // check to see if the char is a vowel or special character
            newWord += character.translateSingleVowel(word[i]); // call the seperate methods depending on if it is a vowel or not and add it to newWord.
        } else {
            newWord += character.translateSingleConstonant(word[i]);
        }
    }
    return newWord; //return the translated word
}


// translateEnglishSentence – takes a single string representing a single English sentence
// as input and returns a string representing the Rövarspråket translation. Make sure to account for punctuation.
std::string Translator::translateEnglishSentence(std::string sentence){
    std::string newSentence = "";                                // string variable that will have all the translated words
    std::string curWord = "";                                   // string variable that will be used to build each word to be translated
    for (int i = 0; i < sentence.length(); i++){                //loop through each character in the sentence
        while (sentence[i] != ' ' && i < sentence.length()){    //check each character to see if it a space or not then add the character to curWord
           curWord += sentence[i];
           i++; 
        }
        newSentence += translateEnglishWord(curWord);           // translate the word created and add it to newSentence
        newSentence += " ";
        curWord = "";

    }

    return newSentence;     //return the new sentence
}

