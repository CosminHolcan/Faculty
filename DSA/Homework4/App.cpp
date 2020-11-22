#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <assert.h>

using namespace std;

void mytest()
{
	cout << "My test\n";
	MultiMap m;
	for (int i = 0; i < 10; i++) {
		m.add(i, i);
	}
	MultiMapIterator it = m.iterator();
	it.next();
	it.next();
	it.next();
	it.next();
	it.next();
	try
	{
		it.jumpBackward(-5);
		assert(false);
	}
	catch (exception ex)
	{
		assert(true);
	}
	try
	{
		it.jumpBackward(6);
		assert(false);
	}
	catch (exception ex)
	{
		assert(true);
	}
	it.first();
	it.next();
	it.next();
	it.next();
	it.jumpBackward(2);
	assert(it.getCurrent() == make_pair(1,1));
}

int main() {
	mytest();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
