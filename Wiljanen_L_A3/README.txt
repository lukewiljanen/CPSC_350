AUTHOR INFO
Luke Wiljanen
2448331
wiljanen@chapman.edu
CPSC-350-03
PA 3: DO YOU SEE WHAT I SEE?

SOURCE FILES
main.cpp, MonoStack.h, SpeakerView.cpp, SpeakerView.h, input.txt

ERRORS
n/a

SOURCES
https://cplusplus.com/reference/sstream/istringstream/istringstream/
Used this source to look up how to sequence a string which I used to get the values 
from the file on each line in my SpeakerView.cpp class in the output() method.

this is the function I used:
std::istringstream stream(line);

https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/
Used this source to find the function to set the arbitrary position in the file back to the top
so that I could cycle and read through the file multiple times. I used this in the output() method as well.

this is the function I used:
inFile.seekg(0);

I also used the arrayStack class we created in class to create my MonoStack class with since that is what the
project description said to do.


RUNNING INSTRUCTIONS
g++ *.cpp -o A3.exe
./A3.exe "input.txt"