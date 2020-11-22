#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

bool isPrime(int nr)
{
	if (nr == 2)
		return true;
	if (nr % 2 == 0)
		return false;
	int d = 3;
	while (d * d <= nr)
	{
		if (nr % d == 0)
			return false;
		d = d + 2;
	}
	return true;
}

int MultiMap::hashFunction(TKey key)
// Complexity : Theta(1)
{
	if (key >= 0)
		return key % this->capacity;
	else
		return (this->capacity - key) % this->capacity;
}

MultiMap::MultiMap() 
/*
Complexity : Theta( capacity)
*/
{
	//TODO - Implementation
	this->capacity = 17;
	this->numberOfElements = 0;
	this->firstEmpty = 0;
	this->elements = new TElem[this->capacity];
	this->next = new int[this->capacity];
	for (int i = 0; i < this->capacity; i++)
	{
		this->elements[i] = NULL_TELEM;
		this->next[i] = -1;
	}
}

void MultiMap::changeFirstEmpty()
/*
n - number of elements
Best case : the first empty element is on the next position - Complexity : Theta(1)
Worst case : somehow, we have to parse thorugh all the elements ( example : add on position 1, 2, 3, 4 then add on 0 ->
             first empty will be set on 5)
Total complexity : O(n)
*/
{
	this->firstEmpty += 1;
	while (this->firstEmpty < this->capacity  && this->elements[this->firstEmpty] != NULL_TELEM)
	{
		this->firstEmpty += 1;
	}
}

void MultiMap::resizeRehash()
/*
n - number of elements
Best case : all elements have different hash values - Complexity : Theta(n)
Worst case : all elements have the same hash value - Complexity : Theta(n^2) ( to add the first element - 1 iteration,
			to add the second one - 2 iterations ... to add the last element - n iterations )
Total Complexity : O(n) amortised
*/
{
	int old_capacity = this->capacity;
	this->capacity = this->capacity * 2;
	while (isPrime(this->capacity) == false)
		this->capacity++;
	TElem* old_elements = this->elements;
	delete []this->next;
	this->elements = new TElem[this->capacity];
	this->next = new int[this->capacity];
	this->numberOfElements = 0;
	this->firstEmpty = 0;
	for (int i = 0; i < this->capacity; i++)
	{
		this->elements[i] = NULL_TELEM;
		this->next[i] = -1;
	}
	for (int i = 0; i < old_capacity; i++)
		this->add(old_elements[i].first, old_elements[i].second);
	delete[]old_elements;
}


void MultiMap::add(TKey c, TValue v) 
/*
n- number of elements
Best case : the element will be added on position returned by hash function - Theta(1)
Worst case : we need a resize and rehash (and in this case considering the worst case also ) - Theta(n^2)
Total Complexity : O(n) amortised
*/
{
	//TODO - Implementation
	if (this->firstEmpty == this->capacity)
	{
		this->resizeRehash();
	}
	int position = this->hashFunction(c);
	if (this->elements[position] == NULL_TELEM)
	{
		this->elements[position] = make_pair(c, v);
		this->next[position] = -1;
		this->numberOfElements++;
		if (position == firstEmpty)
			this->changeFirstEmpty();
	}
	else
	{
		while (this->next[position] != -1)
			position = this->next[position];
		this->elements[this->firstEmpty] = make_pair(c, v);
		this->next[this->firstEmpty] = -1;
		this->next[position] = this->firstEmpty;
		this->changeFirstEmpty();
		this->numberOfElements++;
	}
}


bool MultiMap::remove(TKey c, TValue v)
/*
m - capacity
Best case : the element is not in the container and on position returned by hash function is not any element - Complexity : Theta(1)
Worst case : we remove the element but we have to parse through the all ohter positions to find its previous - Complexity : Theta(m)
Total complexity - O(m)
*/
{
	//TODO - Implementation
	TElem pair = make_pair(c, v);
	int position = this->hashFunction(c), position_aux;
	int previous = -1, previous_aux;
	int index = 0;
	while (position != -1 && this->elements[position] != pair)
	{
		previous = position;
		position = this->next[position];
	}
	if (position == -1)
		return false;
	else
	{
		bool inProcess = true;
		do
		{
			position_aux = this->next[position];
			previous_aux = position;
			while (position_aux != -1 && this->hashFunction(this->elements[position_aux].first) != position)
			{
				previous_aux = position_aux;
				position_aux = this->next[position_aux];
			}
			if (position_aux == -1)
				inProcess = false;
			else
			{
				this->elements[position] = this->elements[position_aux];
				position = position_aux;
				previous = previous_aux;
			}
		} while (inProcess);
		if (previous == -1)
		{
			while (index < this->capacity && previous == -1)
			{
				if (this->next[index] == position)
					previous = index;
				index++;
			}
		}
		if (previous != -1)
			this->next[previous] = this->next[position];
		this->next[position] = -1;
		this->elements[position] = make_pair(-111111, -111111);
		if (position < this->firstEmpty)
			this->firstEmpty = position;
	}
	this->numberOfElements--;
	return true;
}


vector<TValue> MultiMap::search(TKey c)  
/*
Best case : on position returned by hash value is not any element - Complexity : Theta(1)
Worst case : all elements have the same hash value - Complexity : Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	vector<TValue> vectorToReturn;
	int position = this->hashFunction(c);
	while (position != -1)
	{
		if (this->elements[position].first == c)
			vectorToReturn.push_back(this->elements[position].second);
		position = this->next[position];
	}
	return vectorToReturn;
}


int MultiMap::size() const 
// Complexity : Theta(1)
{
	//TODO - Implementation
	return this->numberOfElements;
}

bool MultiMap::isEmpty() const
// Complexity : Theta(1)
{
	//TODO - Implementation
	return this->numberOfElements == 0;
}

MultiMapIterator MultiMap::iterator() const
// Complexity : Theta(1)
{
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap()
// Complexity : Theta(1)
{
	//TODO - Implementation
	delete[]this->elements;
	delete[]this->next;
}

