#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include<iostream>

void test_previous__valid_input__correct_backward_iteration() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	MultiMapIterator im = m.iterator();
	int indexForNext = 3;
	while (indexForNext != 0) {
		im.getCurrent();
		im.next();
		indexForNext--;
	}
	//the iterator indicates (2,600) as the current pair
	int indexForPrev = 3;
	while (indexForPrev != 0) {
		im.previous();
		im.getCurrent();
		indexForPrev--;
	}
	assert(im.getCurrent().first == 1 && im.getCurrent().second == 100);
}


void testAll() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

	vector<TValue> v;
	v = m.search(6);
	assert(v.size() == 0);

	v = m.search(1);
	assert(v.size() == 1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);

	test_previous__valid_input__correct_backward_iteration();
	
}
