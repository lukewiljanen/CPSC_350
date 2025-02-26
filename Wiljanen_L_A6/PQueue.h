// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A6 Spanning the Gamut

#ifndef P_QUEUE_H
#define P_QUEUE_H

#include "DblList.h"

/*
In C++, private inheritance is one of the forms of inheritance that allows 
a derived class to inherit from a base class, but with a restriction on the access 
levels of the inherited members. When a class is privately inherited, it means that 
the public and protected members of the base class become private members of the derived class. 

PQueue inherits privately from the class DblList. 
This means that PQueue is using composition to include DblList as a 
private member rather than establishing an "is-a" relationship through public inheritance.
*/
template <typename T>
class PQueue: private DblList<T>{ //inherit from the DL List but don't make an is-a relationship
public:
  PQueue(bool isMin); //min queue or not
  virtual ~PQueue();
  void add(T data);
  T remove();
  int size();
  bool isEmpty();
  T peek();

private:
  bool isMinQ;
};


template <typename T>
PQueue<T>::PQueue(bool isMin){
  isMinQ = isMin;
}

template <typename T>
PQueue<T>::~PQueue(){
}


template <typename T>
bool PQueue<T>::isEmpty(){
  return DblList<T>::isEmpty();
}

template <typename T>
int PQueue<T>::size(){
  return DblList<T>::size();
}

template <typename T>
T PQueue<T>::peek(){
    if(isMinQ){
        return DblList<T>::get(0); // smallest/ lowest/ min priority always at front

    } else {
        return DblList<T>::get(DblList<T>::m_size-1); // largest/ highest/ max priority always at front
    }
}

template <typename T>
T PQueue<T>::remove(){
  if(isMinQ){
    return DblList<T>::removeFront(); //smallest always at front
  } else{
    return DblList<T>::removeBack(); //largest always at back
  }
}

template <typename T>
void PQueue<T>::add(T d){
  if(isEmpty()){ //well, that's easy. Just add.
    DblList<T>::addFront(d);
    return;
  }
  ListNode<T>* newNode = new ListNode<T>(d);
  int currIdx = 0;
  ListNode<T>* currNode = DblList<T>::m_front;
  while(currNode != NULL && currNode->m_data < d){ //from front, find the right place to add. The < operator better be defined on the class.
    ++currIdx;
    currNode = currNode->m_next;
  }
  DblList<T>::add(currIdx,d); 
		// this is a "hack" 
    // practically we know that if we do this we have a worst scenario runtime 
    // of "2N" however bc in Big Oh notation we drop constants we know that 
    // the Big Oh of this algo is O(n) regardless!
}


#endif
