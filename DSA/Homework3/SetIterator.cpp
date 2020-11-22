#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->currentPosition = this->set.head;
}


void SetIterator::first() 
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->currentPosition = this->set.head;
}


void SetIterator::next()
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == false)
		throw exception();
	this->currentPosition = this->set.next[this->currentPosition];
}


TElem SetIterator::getCurrent()
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == false)
		throw exception();
	return this->set.elements[this->currentPosition];
}

bool SetIterator::valid() const 
/*
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->set.isEmpty() == true || this->currentPosition == -1)
		return false;
	return true;
}

void SetIterator::jumpForward(int k)
{
	if (k <= 0)
		throw exception("The number of steps should be positive !");
	int nr = 0;
	while (nr < k && this->valid() == true)
	{
		this->next();
		nr = nr + 1;
	}
	if (this->valid() == false)
		throw exception("The number of steps is to large !");

}



