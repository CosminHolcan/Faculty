#include "Set.h"
#include "SetITerator.h"


Set::Set()
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->capacity = 10;
	this->numberOfElements = 0;
	this->elements = new TElem[this->capacity];
	this->next = new int[this->capacity];
	this->head = -1;
	for (int i = 0; i < this->capacity-1; i++)
	{
		this->next[i] = i + 1;
	}
	this->next[this->capacity - 1] = -1;
	this->firstEmpty = 0;
}


bool Set::add(TElem elem)
/*
n - number of elements
Best case :  the element is already added on the first position and function returns false - Theta(1)
Worst case : the element will be added at the end of the container, eventually doing a resize - Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	int i;
	if (this->firstEmpty == -1)
	{
		TElem* new_elements = new TElem[this->capacity*2];
		int* new_next = new int[this->capacity*2];
		for (i = 0; i < this->capacity; i++)
		{
			new_elements[i] = this->elements[i];
			new_next[i] = this->next[i];
		}
		for (i = this->capacity; i < this->capacity * 2-1; i++)
		{
			new_next[i] = i + 1;
		}
		new_next[this->capacity * 2 - 1] = -1;
		this->elements = new_elements;
		this->next = new_next;
		this->firstEmpty = this->capacity;
		this->capacity *= 2;
	}
	if (this->head == -1)
	{
		int position = this->firstEmpty;
		this->elements[position] = elem;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[position] = -1;
		this->head = position;
		this->numberOfElements++;
		return true;
	}
	int currentPosition = this->head;
	int previousPosition = -1;
	while (currentPosition != -1)
	{
		if (this->elements[currentPosition] == elem)
			return false;
		previousPosition = currentPosition;
		currentPosition = this->next[currentPosition];
	}
	int position = this->firstEmpty;
	this->firstEmpty = this->next[this->firstEmpty];
	this->elements[position] = elem;
	this->next[previousPosition] = position;
	this->next[position] = -1;
	this->numberOfElements++;
	return true;
}


bool Set::remove(TElem elem) 
/*
n - number of elements
Best case : the element to be removed is on the first position - Theta(1)
Worst case : the element is not in container - Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	int currentPosition = this->head;
	int previousPosition = -1;
	while (currentPosition != -1 && this->elements[currentPosition] != elem)
	{
		previousPosition = currentPosition;
		currentPosition = this->next[currentPosition];
	}
	if (currentPosition == -1)
		return false;
	this->numberOfElements--;
	if (currentPosition == this->head)
		this->head = this->next[this->head];
	else
		this->next[previousPosition] = this->next[currentPosition];
	this->next[currentPosition] = this->firstEmpty;
	this->firstEmpty = currentPosition;
	return true;
}

bool Set::search(TElem elem) const 
/*
n - number of elements
Best case : the element is on the first position - Theta(1)
Worst case : the element is not in container - Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	int currentPosition = this->head;
	while (currentPosition != -1)
	{
		if (this->elements[currentPosition] == elem)
			return true;
		currentPosition = this->next[currentPosition];
	}
	return false;
}


int Set::size() const 
// Complexity : Theta(1)
{
	//TODO - Implementation
	return this->numberOfElements;
}


bool Set::isEmpty() const 
// Complexity : Theta(1)
{
	//TODO - Implementation
	return this->head == -1;
}


Set::~Set() {
	//TODO - Implementation
	delete []this->elements;
	delete []this->next;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


