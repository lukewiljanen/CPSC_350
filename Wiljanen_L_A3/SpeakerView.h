// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A3 DO YOU SEE WHAT I SEE?

#ifndef SPEAKER_VIEW_H
#define SPEAKER_VIEW_H
#include "MonoStack.h"
#include <fstream>

class SpeakerView{
private:
    int inputSize; // The number of columns in the data
    int numRows;    //the number of rows of data 
    std::string getHeights(MonoStack<double>); // method to format the string for how the heights will be printed

public:
    SpeakerView();  //default constructor
    ~SpeakerView(); //default deconstructor
    void output(std::string inputFile); //method that handles all operations for file processesing and outputting
    

};



#endif
