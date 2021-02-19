#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	indexOfKey = col.keys.head;
	indexOfValue = col.keys[indexOfKey].info.second.head;
}

TElem MultiMapIterator::getCurrent() const {
	if (this->valid() == 0) {
		throw exception();
	}
	return pair<TKey, TValue>(col.keys[indexOfKey].info.first, col.keys[indexOfKey].info.second[indexOfValue].info);
}

bool MultiMapIterator::valid() const {
	if (indexOfKey == -1)
		return 0;
	if (indexOfValue == -1)
		return 0;
	return 1;
}

void MultiMapIterator::next() {
	if (this->valid() == 0) {
		throw exception();
	}
	indexOfValue = col.keys[indexOfKey].info.second[indexOfValue].next;
	if (indexOfValue == -1) {
		indexOfKey = col.keys[indexOfKey].next;
		indexOfValue = col.keys[indexOfKey].info.second.head;
	}
}

//bc=ac=wc=O(1)
//we don't have for/while loops so the complexity is quite small
//it's true that if the program goes to the first if finishes faster but this is negligible
void MultiMapIterator::previous(){
	if (this->valid() == 0){
		throw exception();
	}
	indexOfValue = col.keys[indexOfKey].info.second[indexOfValue].prev;
	if (indexOfValue == -1) {
		indexOfKey = col.keys[indexOfKey].prev;
		indexOfValue = col.keys[indexOfKey].info.second.tail;
	}
}

void MultiMapIterator::first() {
	indexOfKey = col.keys.head;
	indexOfValue = col.keys[indexOfKey].info.second.head;
}