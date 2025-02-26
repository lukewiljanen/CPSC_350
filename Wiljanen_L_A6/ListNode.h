// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A6 Spanning the Gamut

#ifndef LIST_NODE_H
#define LIST_NODE_H
#include <cstdlib>
#include "WGraph.h"

// Class for a node in a linked list
template<typename T>
class ListNode{
    public:
    ListNode(T data);
    virtual ~ListNode();
    T m_data;
    ListNode<T>* m_next; //recursive data structure b/c it points to instances of itself
    ListNode<T>* m_prev;
};

template<typename T>
ListNode<T>::ListNode(T data) : m_data(data), m_next(NULL), m_prev(NULL) {
}



template<typename T>
ListNode<T>::~ListNode(){
    m_next = NULL;
    m_prev = NULL;
}
#endif
