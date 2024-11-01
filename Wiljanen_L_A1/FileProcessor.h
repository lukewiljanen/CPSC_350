#pragma once
#include <iostream>
#include <fstream>
#include "Translator.h"

class FileProcessor{

//public methods set up constuctor/ deconstructor and process file method
public:

    FileProcessor();    //default constructor
    ~FileProcessor();   //default deconstructor

    void processFile(std::string inputFile, std::string outputFile); //method used to take in a file and convert it to a translated html file

};