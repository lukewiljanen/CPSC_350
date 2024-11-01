 #include <iostream>
#include <fstream>
#include <string>
#include "Translator.h"
#include "FileProcessor.h"


FileProcessor::FileProcessor(){}
FileProcessor::~FileProcessor(){

}

/*
processFile – takes a string representing the input file  (English) and a string 
representing the output file (where the Rövarspråket translation will be written). 
This method has a void return type. The method should produce a html file that has 
the original English text in bold followed by an empty line, followed by the 
Rövarspråket translation in italics.
*/
void FileProcessor::processFile(std::string inputFile, std::string outputFile){
    
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    std::string line;
    Translator trans;                               
    outFile << "<DOCTYPE html>" << std::endl;       //sets up the doctype to read html
    outFile << "<html>" << std::endl;           
    outFile << "<body>" << std::endl;               //creates the body where the text will go

    if (inFile.is_open()){

        //first print original text in bold letters
        outFile << "<b>";                                   //turns text into bold
        while (getline(inFile, line)){                      //read from the inFile

            if (!line.empty()){
                outFile << line;                            //all in bold letters, the non translated words will be outputted onto the out file
                outFile << std::endl;
            } else {
                std::cout << "Filed failed to open.\n";     //error message in case file could not be opened
                break;
            }
            
        }
        outFile << "<b>";   // ends the bold text
        // //add a space between text
        // outFile << std::endl;
        outFile << "<p>";                       // Creates a new paragraph twice, leaving a space between text
        outFile << "<p>";
        inFile.close();                         //close file
        std::ifstream inFile(inputFile);        //reopen file for translation

        outFile << "<i>";                       //italitizes translated text
        while (getline(inFile, line)){

            if (!line.empty()){
                outFile << trans.translateEnglishSentence(line) << std::endl;   // translates text in italics
            }
        }
        outFile << "<i>" << std::endl;      //ends italiticized letters

        inFile.close();                     //close file
    }
    outFile << "</body>" << std::endl;      //ending of html file
    outFile << "</html>" << std::endl;

}

