#include "Set.h"
#include "SetITerator.h"

Set::Set() 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->number_of_elements = 0;
	this->capacity = 10;
	this->elements = new TElem[this->capacity];
}


bool Set::add(TElem elem) 
/*
Best case - the element is the first in the set - Complexity : Thta(1)
Worst case - the elemet is not in the list and has to be adeed - Complexity : Theta(n)
Average case - Complexity : Theta(n)
Complexity : Theta(1) amortized
*/
{
	//TODO - Implementation
	if (this->search(elem) == true)
		return false;
	if (this->number_of_elements == this->capacity)
	{
		this->capacity *= 2;
		TElem* auxiliary_elemets = new TElem[this->capacity];
		for (int index = 0; index < this->number_of_elements; index++)
			auxiliary_elemets[index] = this->elements[index];
		delete[] this->elements;
		this->elements = auxiliary_elemets;
	}
	this->elements[this->number_of_elements++] = elem;
	return true;
}


bool Set::remove(TElem elem) 
/*
In any case, the algorithm will have n+-1 steps, so
Complexity : Theta(n)
*/
{
	//TODO - Implementation
	int position = -1;
	for (int index=0; index < this->number_of_elements; index ++)
		if (this->elements[index] == elem)
		{
			position = index;
			break;
		}
	if (position == -1)
		return false;
	for (int index = position; index < this->number_of_elements - 1; index++)
		this->elements[index] = this->elements[index + 1];
	this->number_of_elements--;
	return true;
}

bool Set::search(TElem elem) const
/*
Best case - elem is first in set -Complexity : Theta(1)
Worst case - elem is the last in set - Complexity : Theta(n)
Average case - Complexity : Theta(n)
Complexity : O(n)
*/
{
	//TODO - Implementation
	for (int index = 0; index < this->number_of_elements; index++)
		if (this->elements[index] == elem)
			return true;
	return false;
}


int Set::size() const 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	return this->number_of_elements;
}


bool Set::isEmpty() const 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	return this->number_of_elements == 0;
}


Set::~Set() {
	//TODO - Implementation
	delete[] this->elements;
}


SetIterator Set::iterator() const 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	return SetIterator(*this);
}


