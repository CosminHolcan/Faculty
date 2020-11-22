#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
	friend class SortedMap;
private:
	SortedMap& map;
	SMIterator(SortedMap& mapionar);

	//TODO - Representation
	Node* it;

public:
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
	TElem remove();
};

