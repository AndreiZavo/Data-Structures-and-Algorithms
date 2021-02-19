#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	current_position = 0;
	bag_elements = c.elements;
	bag_length = c.length_of_bag;
}

void BagIterator::first() {
	current_position = 0;
}


void BagIterator::next() {
	if (current_position >= bag_length) {
		throw exception();
	}
	current_position++;
}


bool BagIterator::valid() const {
	if (current_position >= bag_length) {
		return false;
	}
	return true;
}



TElem BagIterator::getCurrent() const
{
	if (current_position >= bag_length) {
		throw exception();
	}
	return bag_elements[current_position];
}
