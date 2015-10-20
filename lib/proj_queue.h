#ifndef PROJ_QUEUE_HEADER_INCLUDED
#define PROJ_QUEUE_HEADER_INCLUDED

#include "proj_set.h"

class EmptyQueueException : public std::exception {
	
};

template <class T>
struct Node {
	T data;
	struct Node *next;
};

template <class T>
class Queue {
  
  public:
	//[WORKING] constructor
	Queue();
	
	//[WORKING] adds item to the end of queue
    void enqueue(const T & item);

    //[WORKING] removes the oldest element of the queue
    //Note: throws EmptyQueueException if queue is empty
    void dequeue(); 

    //[WORKING] returns the oldest element of the queue
    //Note: throws EmptyQueueException if the queue is empty
    const T & peekFront();

    //[WORKING] returns whether the queue is empty
    bool isEmpty();
       
    
  private:
    Node<T>* tail;
    Node<T>* head;

};

#include "proj_queue_impl.cpp"
#endif