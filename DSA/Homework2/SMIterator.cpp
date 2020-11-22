#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(SortedMap& m) : map(m)
/*
Simple initialization, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->it = m.head;
}

void SMIterator::first() 
/*
Just one case, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->it = map.head;
}

void SMIterator::next()
/*
Just one case, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == true)
		this->it = this->it->next;
	else
		throw exception();
}

bool SMIterator::valid() const 
/*
Just one case, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->map.isEmpty() == true || this->it == nullptr)
		return false;
	return true;

}

TElem SMIterator::getCurrent() const
/*
Just one case, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	if (this->valid() == true)
		return this->it->info;
	else
		throw exception();
}

TElem SMIterator::remove()
/*
Just one case, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	if (this->valid() == true)
	{
		TElem elemToReturn = this->it->info;
		TKey key = elemToReturn.first;
		this->it = this->it->next;
		TValue val = this->map.remove(key);
		return elemToReturn;
	}
	else
		throw exception();
}