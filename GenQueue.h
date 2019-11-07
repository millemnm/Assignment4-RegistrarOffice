#ifndef GENQUEUE_H
#define GENQUEUE_H
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "DList.h"

using namespace std;

template <class type>
class GenQueue : private DList<type>
{
	public:
		GenQueue();//constructor
		~GenQueue();

		void insert(type data);
		type remove();
		type peek();
		bool isEmpty();
		int getSize();

	private:
		DList<type> *myQueue;
};

//default constructor
template <class type>
GenQueue<type>::GenQueue(){
	myQueue = new DList<type>();
}

template <class type>
GenQueue<type>::~GenQueue(){
	delete[] myQueue;
}

template <class type>
void GenQueue<type>::insert(type data){
	myQueue->addBack(data);
}

template <class type>
type GenQueue<type>::remove(){
	return myQueue->removeHead();
}

template <class type>
type GenQueue<type>::peek(){
	return myQueue->getFront();
}

template <class type>
bool GenQueue<type>::isEmpty(){
	return myQueue->isEmpty();
}

template <class type>
int GenQueue<type>::getSize(){
	return myQueue->getSize();
}

#endif
