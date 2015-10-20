#ifndef PROJ_QUEUE_IMPL_INCLUDED
#define PROJ_QUEUE_IMPL_INCLUDED

//implementation of queue


//[WORKING] constructor
template <class T>
Queue<T>::Queue() 
{
	head = NULL;
	tail = NULL;
}

//[WORKING] adds item to the end of queue
template <class T>
void Queue<T>::enqueue(const T & item) 
{	
	Node<T> *temp = new Node<T>;
	
	temp->data = item;
	temp->next = NULL;
	
	if(isEmpty()) head = temp;
	else tail->next = temp;
	
	tail = temp;
}

//[WORKING] removes the oldest element of the queue
//Note: throws EmptyQueueException if queue is empty
template <class T>
void Queue<T>::dequeue() 
{
	Node<T>* temp = new Node<T>;
	
	if(isEmpty()) throw EmptyQueueException();
	else
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

//[WORKING] returns the oldest element of the queue
//Note: throws EmptyQueueException if the queue is empty
template <class T>
const T & Queue<T>::peekFront() 
{
	if(isEmpty()) throw EmptyQueueException();
	return head->data;
}

//[WORKING] returns whether the queue is empty
template <class T>
bool Queue<T>::isEmpty() 
{
	return (head == NULL);
}


#endif