#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) 
/*
m - capacity
Best case : element on first position - Compleixty : Theta(1)
Worst case : no elements - Complexity : Theta(m)
Total complexity : O(m)
*/
{
	//TODO - Implementation
	this->currentPosition = 0;
	while (this->col.elements[currentPosition] == NULL_TELEM && this->currentPosition < this->col.capacity)
		this->currentPosition++;
}

TElem MultiMapIterator::getCurrent() const
// Complexity : Theta(1)
{
	//TODO - Implementation
	if (this->valid())
		return this->col.elements[this->currentPosition];
	else
		throw exception();
}

bool MultiMapIterator::valid() const
// Complexity : Theta(1)
{
	//TODO - Implementation
	return (this->col.isEmpty() == false && this->currentPosition < this->col.capacity && this->currentPosition >= 0);
}

void MultiMapIterator::next() 
/*
Best case : we found a new element on the next position - Complexity : Theta(1)
Worst case : after the element on first position we don't have any other elements - Complexity : Theta(m)
Total complexity : O(m)
*/
{
	//TODO - Implementation
	if (this->valid())
	{
		this->currentPosition++;
		while (this->col.elements[currentPosition] == NULL_TELEM && this->currentPosition < this->col.capacity)
			this->currentPosition++;
	}
	else throw exception();
}

void MultiMapIterator::first()
/*
m - capacity
Best case: element on first position - Compleixty : Theta(1)
Worst case: no elements - Complexity : Theta(m)
Total complexity : O(m)
*/
{
	//TODO - Implementation
	this->currentPosition = 0;
	while (this->col.elements[currentPosition] == NULL_TELEM && this->currentPosition < this->col.capacity)
		this->currentPosition++;
}

void MultiMapIterator::previous()
/*
m - capacity
Best case : element is on the previous position - Complexity : Theta(1)
Worst case : we have to go from the last position to the first - Complexity : Theta(m)
Total complexity : O(m)
*/
{
	if (this->valid())
	{
		this->currentPosition--;
		while (this->col.elements[this->currentPosition] == NULL_TELEM && this->currentPosition >= 0)
			this->currentPosition--;
	}
}

void MultiMapIterator::jumpBackward(int k)
/*
Best case : k < 0, this will make iterator invalid - Complexity : Theta(1)
Worst case : we have to go from last position to the first - Complexity : Theta(m)
Total complexity : O(m)
*/
{
	if (k <= 0)
		throw exception("The number of steps should be positive !");
	int nr = 0;
	while (nr < k && this->valid() == true)
	{
		this->previous();
		nr = nr + 1;
	}
	if (this->valid() == false)
		throw exception("The number of steps is to large !");
}

