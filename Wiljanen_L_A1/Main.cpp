#include "Translator.h"
#include "Model.h"
#include <iostream>
#include "FileProcessor.h"


int main(int argc, char* argv[]){                   //set up main method to take command line args

    FileProcessor fp;                               //create a file processor object
    fp.processFile(argv[1], "translation.html");    // run the translation method with the .txt file taken in
    return 0;

}  