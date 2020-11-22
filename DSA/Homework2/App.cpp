#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"
#include "SMIterator.h"
#include <assert.h>
#include <iostream>
using namespace std;

bool relationIncresing(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void myTest()
{
    cout << "My test" << '\n';
    SortedMap sm(relationIncresing);
    sm.add(5, 6);
    sm.add(3, 4);
    sm.add(1, 2);
    SMIterator it = sm.iterator();
    it.first();
    TElem e(1, 2), e2(3, 4), e3(5, 6);
    assert(sm.search(1) == 2);
    assert(it.remove() == e);
    assert(sm.search(1) == NULL_TVALUE);
    assert(it.remove() == e2);
    assert(it.remove() == e3);
    assert(sm.isEmpty() == true);
    try {
        it.remove();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
}


int main() {
	testAll();
	testAllExtended();
    myTest();
	cout << "That's all!" << endl;
	system("pause");
	return 0;
}