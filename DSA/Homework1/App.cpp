#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <assert.h>
using namespace std;

void testPrevious()
{
	Set s;
	assert(s.add(15) == true);
	assert(s.add(12) == true);
	assert(s.add(17) == true);
	assert(s.add(10) == true);
	SetIterator it = s.iterator();
	assert(it.getCurrent() == 15);
	it.next();
	it.next();
	it.previous();
	assert(it.getCurrent() == 12);
	it.first();
	it.previous();
	assert(it.valid() == false);
}


int main() {

	testAll();
	testAllExtended();

	testPrevious();

	cout << "That's all!" << endl;

	system("pause");

}



