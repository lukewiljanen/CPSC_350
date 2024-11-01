// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A3 DO YOU SEE WHAT I SEE?

#include <iostream>
#include "SpeakerView.h"
#include <string>
#include <fstream>
#include <sstream>

/*
The Speaker View class Takes a file into its output method and uses a monotonically decreasing stack to 
process the file and output the number of people that can see in each column and what their heights are.
*/


SpeakerView::SpeakerView(){
    inputSize = 0;
    numRows = 0;
}


SpeakerView::~SpeakerView(){}

void SpeakerView::output(std::string inputFile){

    std::ifstream inFile(inputFile);
    std::string line;

    if (!inFile.is_open()){
            std::cout << "Could not open file." << std::endl;
    }
    
    // This while loop gets the dimensions of the data in the file so that the stack and for loop dimensions can be established after
    while (getline(inFile, line)){
        if(line == "BEGIN"){    //first line of the file
            continue;
        }

        double dbl;
        std::istringstream stream(line);
        while (stream >> dbl && numRows < 1){
            inputSize++;
        }

        if(line == "END"){  //ends the loop
            break;
        }
        numRows++;
        
    }
    inFile.seekg(0); //sets the file readeing mark back to the top

    for (int i = 0; i < inputSize; i++){    // loops through each column, making and running a stack for each one

        MonoStack<double> columnViews(numRows, 'd');    // create a MonoStack object with that is monotonically decreasing
        
        //std::string line;

        while(getline(inFile, line)){   //read from the file
            int currCol = 0;
            if(line == "BEGIN"){    //first line of the file
                continue;
            }
            if(line == "END"){  //ends the loop
                break;
            }
            
            std::istringstream stream(line);    //gets the number at the file line

            double numb;    //variable to hold to number value recieved

            while (stream >> numb){     // puts the value recieved into the double variable
                
                if (currCol == i){  // if the column that the number is in is in the column of the current stack, push it onto the stack
                    columnViews.push(numb);
                }
                currCol++;  // increment the column to keep track of what column the reader is in
            }
            
        }
        std::cout << "In column " << i << " there are " << columnViews.size() << " that can see. There heights are: " << getHeights(columnViews) << " inches." << std::endl;
        
        
        inFile.seekg(0); //sets the file back to the start for reading
    }
    inFile.close(); 
    
}

std::string SpeakerView::getHeights(MonoStack<double> stk){
    std::string str = "";   // set up empty string to add heights to
    while (!stk.isEmpty())  // run until there are no values in the stack
    {
        double temp = stk.pop();    //pop value from the stack
        str += std::to_string(temp);    //convert the value to a string
        if (stk.isEmpty()){             //this is for formatting to know if there should be a comma after the value.
            break;
        }
        str += ", ";    
    }

    return str;
}
