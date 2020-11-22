#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;


SetIterator::SetIterator(const Set& m) : set(m)
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->index = 0;
}


void SetIterator::first() 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->index = 0;
}


void SetIterator::next() 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == true)
		this->index++;
	else
		throw exception();
}

void SetIterator::previous()
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	if (this->valid() == true)
		this->index--;
	else
		throw exception();
}


TElem SetIterator::getCurrent()
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == true)
		return set.elements[index];
	else
		throw exception();
}

bool SetIterator::valid() const
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (index >= set.size() || set.isEmpty() == true || index < 0)
		return false;
	return true;
}



