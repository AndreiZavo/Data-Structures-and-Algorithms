#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//constructor
	capacity = 1;
	length_of_bag = 0;
	elements = new TElem[capacity];
	frequencies = new TElem[capacity];
}


void Bag::add(TElem elem) {
	//best case is when the new element doesn't exist and we have enough space in the vector; complexity is theta(n)
	//worst case is when we need to duplicate the size of the vector and the element already exists in the vector; complexity is theta(2*n)
	int new_frequency = 0;
	if (capacity == length_of_bag) {
		capacity *= 2;
		TElem* new_array = new TElem[capacity];
		TElem* new_frequencies_array = new TElem[capacity];
		for (int index = 0; index < length_of_bag; index++) {
			new_array[index] = elements[index];
			new_frequencies_array[index] = frequencies[index];
		}
		delete[] elements;
		elements = new_array;
		delete[] frequencies;
		frequencies = new_frequencies_array;
	}
	if (!search(elem)) {
		elements[length_of_bag] = elem;
		frequencies[length_of_bag] = 1;
		length_of_bag++;
	}
	else {
		elements[length_of_bag] = elem;
		new_frequency = nrOccurrences(elem) + 1;
		for (int index = 0; index < length_of_bag; index++) {
			if (elements[index] == elem) {
				frequencies[index] = new_frequency;
			}
		}
		length_of_bag++;
	}
}


bool Bag::remove(TElem elem) {
	//best case: the complexity is theta(n) due to the first for and we don't find the element
	//worst case which is also the average case is when we found the element and the second for is executed; complexity is theta(2 * n)
	bool element_found = false;
	int element_found_position = -1;
	for (int i = 0; i < length_of_bag; i++) {
		if (elements[i] == elem) {
			element_found = true;
			element_found_position = i;
			elements[i] == NULL;
			frequencies[i]--;
		}
	}
	if (element_found) {
		for (int i = element_found_position; i < length_of_bag - 1; i++) {
			elements[i] = elements[i + 1];
			frequencies[i] = frequencies[i + 1];
		}
		length_of_bag--;
	}
	return element_found;
}


bool Bag::search(TElem elem) const {
	//the complexity is O(n) due to the for
	// the best complexity is theta(1) in the case that the first element is the one that we're looking for
	//the worst is theta(n) in the case we don't find the desired number
	for (int index = 0; index < length_of_bag; index++) {
		if (elements[index] == elem) {
			return true;
		}
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	//the complexity is O(n) due to the for
	// the best complexity is theta(1) in the case that the first element is the one that we're looking for
	//the worst is theta(n) in the case we don't find the desired number 
	for (int index = 0; index < length_of_bag; index++) {
		if (elements[index] == elem) {
			return frequencies[index];
		}
	}
	return 0;
}


int Bag::size() const {
	// complexity is O(1) we just return
	return length_of_bag;
}


bool Bag::isEmpty() const {
	//the complexity is O(n) due to the for 
	for (int index = 0; index < length_of_bag; index++) {
		if (elements[index] != NULL) {
			return false;
		}
	}
	return true;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

int Bag::elementsWithMinimumFrequency() const {
	//the complexity is O(2 * n) due to the two fors
	if (isEmpty())
		return 0;
	else {
		int minimum_frequency = frequencies[0];
		int number_with_minimum_frequency = 0;
		for (int index = 1; index < length_of_bag; index++) {   // this for gives the O(n) complexity
			if (frequencies[index] < minimum_frequency)
				minimum_frequency = frequencies[index];
		}
		for (int index = 0; index < length_of_bag; index++) { //and this one doubles it 
			if (frequencies[index] == minimum_frequency) {
				number_with_minimum_frequency++;
			}
		}
		return number_with_minimum_frequency;
	}
}

Bag::~Bag() {
	delete[] elements;
	delete[] frequencies;
}

