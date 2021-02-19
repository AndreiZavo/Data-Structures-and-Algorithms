#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIteratedList;
private:
	Node* current_node;
	const SortedIteratedList& list;

	ListIterator(const SortedIteratedList& list);
	
public:
	void first();
	void next();
	void jumpForward(int k);
	bool valid() const;
	TComp getCurrent() const;
};


