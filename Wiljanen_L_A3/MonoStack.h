// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A3 DO YOU SEE WHAT I SEE?

#ifndef MONO_STACK_H
#define MONO_STACK_H
#include <iostream> 

template <typename T>
class MonoStack{
    public:
        MonoStack(int iSize, char o);
        ~MonoStack();
        void push(T c); //add to the top
        T pop(); //remove from the top
        T peek(); //return the top without removing
        bool isFull();
        bool isEmpty();
        int size();

    private:
        T* stackArr;
        int count; //number of items currently in the stack
        int maxSize; //max number of things in the stack
        int top; //index of the current top of the stack
        char stackType; // o==i for monotonically increasing stack and o==d for monotonically decreasing stack
};


template <typename T>
MonoStack<T>::MonoStack(int iSize, char o){
    stackArr = new T[iSize];
    maxSize = iSize;
    count = 0;
    top = -1;
    stackType = o;
}
template <typename T>
MonoStack<T>::~MonoStack(){
    //std::cout << "clearing a TStack obj!" << std::endl;
    if (!stackArr){
        delete[] stackArr;
        stackArr = nullptr;
    }
    
}
template <typename T>
bool MonoStack<T>::isFull(){
    return (count == maxSize);
}
template <typename T>
bool MonoStack<T>::isEmpty(){
    return (count == 0);
}
template <typename T>
int MonoStack<T>::size(){
    return count;
}

/*
which must ensure that the values remain in monotonically increasing or decreasing order. 
This means that for a monotonically increasing stack, to push a value of X on the stack, 
we must first pop and discard all values in the stack that are larger than X. Similarly, 
for a monotonically decreasing stack, to push a value of X on the stack, we must first 
pop and discard all values in the stack that are smaller than X. All other operations stay the same.
*/
template <typename T>
void MonoStack<T>::push(T c){
    if(isFull()){
        T* temp = new T[2*maxSize];
        for(int i = 0; i < maxSize; ++i){
            temp[i] = stackArr[i];
        }
        maxSize *= 2;
        delete[] stackArr;
        stackArr = temp;
    }
    if (isEmpty()){
            stackArr[++top] = c;
            ++count;
    } 
    else if (stackType == 'i'){ //monotonically increasing
        if (c < stackArr[0]){
            T* temp = new T[maxSize];
            int ind = 0;
            while (c < stackArr[top] && !isEmpty()){
                temp[ind] = pop();
                ind++;
            }
            stackArr[++top] = c;
            count++;
            ind--;
            while (ind >= 0){
                stackArr[++top] = temp[ind];
                ++count;
                ind--;
            }
        }
    } else {    //monotonically decreasing
        if (c > stackArr[0]){   //checks to see if the value follows the rule of a monotically decreasing stack
            T* temp = new T[maxSize];   //create a temporary array for values that c is larger than
            int ind = 0;
            while (c > stackArr[top] && !isEmpty()){    //pop and add all values from the array that c is larger than and add them to the temp array
                temp[ind] = pop();
                ind++;
            }
            stackArr[++top] = c;    //add c at the top
            count++;
            ind--;
            while (ind >= 0){   //add back values to the stack that are in the temp array
                stackArr[++top] = temp[ind];
                ++count;
                ind--;
            }
            
        }
    }
}
template <typename T>
T MonoStack<T>::pop(){
    --count;
    return stackArr[top--];
}
template <typename T>
T MonoStack<T>::peek(){
    return stackArr[top];
}
#endif
