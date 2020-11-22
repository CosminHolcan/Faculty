#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) 
/*
Simple initialization, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	this->relation = r;
	this->head = nullptr;
	this->numberOfElements = 0;
}

TValue SortedMap::add(TKey k, TValue v) 
/*
Best case : the element will be added first - Complexity : Theta(1)
Worst case : the element will be added at the end of container - Complexity : Theta(n)
Average case - Complexity : Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	Node* node = new Node();
	TElem p(k, v);
	node->info = p;
	if (this->head == nullptr)
	{
		this->head = node;
		node->next = nullptr;
		this->numberOfElements++;
		return NULL_TVALUE;
	} 
	if (this->relation(p.first, this->head->info.first) == true)
	{
		if (p.first == this->head->info.first)
		{
			TValue valueToReturn = this->head->info.second;
			this->head->info = p;
			return valueToReturn;
		}
		node->next = this->head;
		this->head = node;
		this->numberOfElements++;
		return NULL_TVALUE;
	}
	else
	{
		Node* previous = nullptr;
		Node* current = this->head;
		while (current !=  nullptr && this->relation(current->info.first, node->info.first) == true)
		{
			previous = current;
			current = current->next;
		}
		if (previous->info.first == node->info.first)
		{
			TValue valueToReturn = previous->info.second;
			previous->info = node->info;
			return valueToReturn;
		}
		node->next = previous->next;
		previous->next = node;
		this->numberOfElements++;
		return NULL_TVALUE;
	}
}

TValue SortedMap::search(TKey k) const 
/*
Best case : the element to find is the first - Complexity : Theta(1)
Worst case : the element to find is at the end of container - Complexity : Theta(n)
Average case - Complexity : Theta(n)
Total complexity : O(n)
*/
{
	//TODO - Implementation
	if (this->head == nullptr)
		return NULL_TVALUE;
	Node* current = this->head;
	while (current != nullptr)
	{
		if (current->info.first == k)
			return current->info.second;
		current = current->next;
	}
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) 
/*
Best case : the element to be removed is the first - Complexity : Theta(1)
Worst case : the element to be removed is at the end of container - Complexity : Theta(n)
Average case - Complexity : Theta(n)
Total complexity : O(n)
*/ 
{
	//TODO - Implementation
	if (this->head == nullptr)
		return NULL_TVALUE;
	if (this->head->info.first == k)
	{
		TValue valueToReturn = this->head->info.second;
		Node* nodeToDelete = this->head;
		this->head = this->head->next;
		this->numberOfElements--;
		delete nodeToDelete;
		return valueToReturn;
	}
	Node* current = this->head;
	Node* previous = nullptr;
	while (current != nullptr && current->info.first != k)
	{
		previous = current;
		current = current->next;
	}
	if (current == nullptr)
		return NULL_TVALUE;
	TValue valueToReturn = current->info.second;
	previous->next = current->next;
	this->numberOfElements--;
	delete current;
	return valueToReturn;
}

int SortedMap::size() const
/*
Just return the size of the container wich is an attribute of class, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	return this->numberOfElements;
}

bool SortedMap::isEmpty() const
/*
Just check is the number of elements is 0, no best case, worst case, average case
Complexity : Theta(1)
*/
{
	//TODO - Implementation
	return this->numberOfElements == 0;
}

SMIterator SortedMap::iterator() 
/*
No best case, worst case, average case
Complexity : Theta(1)
*/
{
	return SMIterator(*this);
}

SortedMap::~SortedMap() 
/*
Just one case, parse the whole container to remove any element
Complexity : Theta(n)
*/
{
	//TODO - Implementation
	Node* current = this->head;
	Node* previous = nullptr;
	while (current != nullptr)
	{
		previous = current;
		current = current->next;
		delete previous;
	}
}
