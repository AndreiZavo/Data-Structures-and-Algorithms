#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

//The complexity is O(1)
ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	this->current_node = this->list.head;
}

//The complexity is O(1)
void ListIterator::first() {
	this->current_node = this->list.head;
}

//The complexity is O(1)
void ListIterator::next() {
	if (this->current_node != NULL) {
		current_node = current_node->next;
	}
	else {
		throw exception("No more nodes!");
	}
}

//The best complexity is Theta(1).This happens when one of the first 2 ifs is executed
//	or when there is just one node left in the list
//The worst complexity is O(n) and it is when the while executes completly
//The average case is O(n)
void ListIterator::jumpForward(int k)
{
	if (k < 1) {
		throw exception("The step is 0 or less");
	}
	if (this->list.size() < k) {
		throw exception("The list is to small");
	}
	while (k) {
		current_node = current_node->next;
		if (this->current_node == NULL) {
			throw exception("No mode nodes");
		}
		k--;
	}
}

//The complexity is O(1)
bool ListIterator::valid() const {
	if (current_node == NULL) {
		return false;
	}
	else {
		return true;
	}
}

//The complexity is O(1)
TComp ListIterator::getCurrent() const {
	if (current_node == NULL) {
		throw exception("No nodes to display");
	}
	int current_value = current_node->value;
	return current_value;
}


