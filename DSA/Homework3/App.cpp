#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <assert.h>
using namespace std;

void mytest()
{
	cout << "My test\n";
	Set s;
	s.add(1);
	s.add(5);
	s.add(17);
	s.add(10);
	s.add(8);
	SetIterator it = s.iterator();
	it.first();
	it.jumpForward(3);
	assert(it.getCurrent() == 10);
	try
	{
		it.jumpForward(-3);
		assert (false);
	}
	catch (exception& ex)
	{
		assert(true);
	}
	try
	{
		it.jumpForward(3);
		assert(false);
	}
	catch (exception& ex)
	{
		assert(true);
	}
}


int main() {

	testAll();
	testAllExtended();
	mytest();
	cout << "That's all!" << endl;
	system("pause");

}
