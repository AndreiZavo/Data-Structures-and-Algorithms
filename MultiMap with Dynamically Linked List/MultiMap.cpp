#pragma once
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	numberOfPairs = 0;
}

// bc =  O(1)
// ac = wc(resize) = O(n)
void MultiMap::add(TKey c, TValue v) {
	if (this->isEmpty() == 0) {
		int currentKey = keys.head;
		while (currentKey != -1) {						//ac and wc are due to this while in the case we will iterate through the whole MultiMap
			if (keys[currentKey].info.first == c) {
				keys[currentKey].info.second.add(v);
				numberOfPairs++;
				return;
			}
			currentKey = keys[currentKey].next;
		}
	}
	DLLA<TValue> newDlla;
	newDlla.add(v);

	this->keys.add(pair<TKey, DLLA<TValue> >(c, newDlla));
	numberOfPairs++;
}

//bc =O(1)
// wc=ac = O(numberOfKeys*numberOfElemens)
bool MultiMap::remove(TKey c, TValue v) {
	if (this->isEmpty()) {
		return 0;
	}
	int currentKey = keys.head;
	while (currentKey != -1) {												//ac and wc are due to this while in the case we will iterate through all keys MultiMap
		if (keys[currentKey].info.first == c) {
			int index = keys[currentKey].info.second.head;
			while (index != -1) {											//and this while in the case we will iterate through all values of every key MultiMap
				if (keys[currentKey].info.second[index].info == v) {
					keys[currentKey].info.second.deleteAtPosition(index);
					numberOfPairs--;
					if (keys[currentKey].info.second.sizeOf() == 0) {
						keys.deleteAtPosition(currentKey);
					}
					return 1;
				}
				index = keys[currentKey].info.second[index].next;
			}
			return 0;
		}
		currentKey = keys[currentKey].next;
	}
	return 0;
}

// bc = O(1)
// wc = ac = O(numberOfKeys+numberElementsForGivenKey)
vector<TValue> MultiMap::search(TKey c) const {
	if (this->isEmpty()) {
		return vector<TValue>();
	}
	int currentKey = keys.head;
	while (currentKey != -1) {														//ac and wc are due to this while in the case we will iterate through all keys MultiMap
		if (keys[currentKey].info.first == c) {
			vector<TValue> valueVector;
			int index = keys[currentKey].info.second.head;
			while (index != -1) {													//and this while in the case we will iterate through all values of the key MultiMap
				valueVector.push_back(keys[currentKey].info.second[index].info);
				index = keys[currentKey].info.second[index].next;
			}
			return valueVector;
		}
		currentKey = keys[currentKey].next;
	}
	return vector<TValue>();
}


int MultiMap::size() const {
	return this->numberOfPairs;
}


bool MultiMap::isEmpty() const {
	if (this->keys.head == -1) {
		return 1;
	}
	return 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	
}


