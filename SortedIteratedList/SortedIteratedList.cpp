#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->relation = r;
	this->head = NULL;
}

//The complexity is O(n) due to the while instruction
int SortedIteratedList::size() const {
	Node* current = this->head;
	Relation relation = this->relation;
	int size = 0;
	while (current != NULL) {
		size++;
		current = current->next;
	}
	return size;
}

//The complexity is O(1)
bool SortedIteratedList::isEmpty() const {
	return (this->head == NULL);
}

//The complexity is O(1)
ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}

//The worst case is a complexity of Theta(n)
//The best case is O(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (!poz.valid()) {
		throw exception("exception");
	}
	Node* current_node = this->head;
	while (current_node != NULL and current_node->value != poz.getCurrent()) {
		current_node = current_node->next;
	}
	if (current_node == NULL) {
		throw exception("The possition is not valid!\n");
	}
	else {
		return poz.getCurrent();
	}
}

//The worst case is a complexity of Theta(n)
//The best case is O(1)
TComp SortedIteratedList::remove(ListIterator& poz) {
	Node* current_node = this->head;
	Node* previous_node = NULL;
	int value_deleted = 0;
	while (current_node != NULL and current_node->value != poz.getCurrent()) {
		previous_node = current_node;
		current_node = current_node->next;
	}
	if(current_node != NULL and previous_node == NULL){
		value_deleted = current_node->value;
		this->head = this->head->next;
	}
	else {
		if (current_node != NULL) {
			value_deleted = current_node->value;
			previous_node->next = current_node->next;
		}
		else {
			throw exception("The node is not here!");
		}
	}
	poz.next();
	delete current_node;
	return value_deleted;
}

//The worst case is a complexity of Theta(n)
//The best case is O(1)
ListIterator SortedIteratedList::search(TComp e) const {
	ListIterator it = ListIterator(*this);
	while (it.valid() and it.getCurrent() != e) {
		it.next();
	}
	return it;
}

//The worst case is a complexity of Theta(n)
//The best case is O(1)
void SortedIteratedList::add(TComp e) {
	Node* new_node = new Node;
	new_node->value = e;
	new_node->next = NULL;
	if (this->head == NULL) {
		this->head = new_node;
	}
	else {
		if (relation(e, this->head->value)) {
			new_node->next = this->head;
			this->head = new_node;
		}
		else {
			Node* previous = NULL;
			Node* current_node = this->head;
			while (current_node->next != NULL and relation(current_node->value, e)) {
				previous = current_node;
				current_node = current_node->next;
			}
			if (current_node->next == NULL) {
				if (relation(current_node->value, e)) {
					current_node->next = new_node;
					new_node->next = NULL;
				}
				else {
					previous->next = new_node;
					new_node->next = current_node;
				}
			}
			else {
				previous->next = new_node;
				new_node->next = current_node;
			}
		}
	}
}

//The complexity is O(n)
SortedIteratedList::~SortedIteratedList() {
	Node* current = this->head;
	while (current != NULL) {
		Node* node_to_delete = current;
		current = current->next;
		delete node_to_delete;

	}
}
