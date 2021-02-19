#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iterator>

template <typename TElement>

struct DllaNode {
	TElement info;
	int next;
	int prev;
};

template <typename elementType>
class DLLA {
private:
	int capacity;
	int size;
	int firstEmpty;
	DllaNode<elementType>* elements;

public:

	int head;
	int tail;
	DLLA(int capacity = 1);

	DLLA(const DLLA& vector);
	
	int sizeOf() const { return this->size; }
	
	void add(elementType element);
	
	bool deleteAtPosition(int position);
	
	DLLA<elementType>& operator=(const DLLA& vector);
	
	DllaNode<elementType>& operator[](int position);
	
	const DllaNode<elementType>& operator[](int position) const;

	~DLLA();

private:
	void resize();
};

template<typename elementType>
inline DLLA<elementType>::DLLA(int capacity) : capacity(capacity), size(0), head(-1), tail(-1), firstEmpty(0) 
{
	this->elements = new DllaNode<elementType>[this->capacity];
	for (int index = 0; index < capacity - 1; index++) {
		elements[index].next = index + 1;
		elements[index].prev = index - 1;
	}
	elements[capacity - 1].next = -1;
	elements[capacity - 1].prev = capacity - 2;
}


template<typename elementType>
inline DLLA<elementType>::DLLA(const DLLA& vector)
{
	this->capacity = vector.capacity;
	this->size = vector.size;
	this->head = vector.head;
	this->tail = vector.tail;
	this->firstEmpty = vector.firstEmpty;
	this->elements = new DllaNode<elementType>[this->capacity];
	for (int index = 0; index < this->capacity; index++) {
		this->elements[index] = vector.elements[index];
	}
}

template<typename elementType>
inline void DLLA<elementType>::add(elementType element)
{
	if (head == -1) {
		head = this->firstEmpty;
		tail = this->firstEmpty;
		elements[head].info = element;

		this->firstEmpty = elements[this->firstEmpty].next;
		elements[head].next = -1;
		this->size++;
		return;
	}
	if (this->size == this->capacity) {
		this->resize();
	}
		elements[tail].next = this->firstEmpty;
		elements[firstEmpty].prev = this->tail;

		this->tail = this->firstEmpty;
		this->firstEmpty = elements[tail].next;

		elements[tail].info = element;
		elements[tail].next = -1;

		this->size++;
}

template<typename elementType>
inline bool DLLA<elementType>::deleteAtPosition(int position)
{
	if (position == tail) {
		tail = elements[tail].prev;
		elements[tail].next = -1;
	}
	else {
		if (position == head) {
			head = elements[position].next;
			elements[head].prev = -1;
		}
		else {
			int prevPos = elements[position].prev;
			int nextPos = elements[position].next;
			elements[prevPos].next = nextPos;
			elements[nextPos].prev = prevPos;
		}
	}
	elements[position].prev = -1;
	elements[position].next = firstEmpty;
	firstEmpty = position;
	this->size--;
	if (this->size == 0) {
		head = -1;
	}
	return 1;
}

template<typename elementType>
inline DLLA<elementType>& DLLA<elementType>::operator=(const DLLA& vector)
{
	if (this == &vector) {
		return *this;
	}
	this->capacity = vector.capacity;
	this->size = vector.size;
	this->head = vector.head;
	this->tail = vector.tail;
	this->firstEmpty = vector.firstEmpty;
	delete[] this->elements;
	this->elements = new DllaNode<elementType>[this->capacity];
	for (int index = 0; index < this->capacity; index++)
		this->elements[index] = vector.elements[index];

	return *this;

}

template<typename elementType>
inline DllaNode<elementType>& DLLA<elementType>::operator[](int position)
{
	return this->elements[position];
}

template<typename elementType>
inline const DllaNode<elementType>& DLLA<elementType>::operator[](int position) const
{
	return this->elements[position];
}



template<typename elementType>
inline DLLA<elementType>::~DLLA()
{
	if (elements == nullptr) {
		return;
	}
	elements = nullptr;
}

template<typename elementType>
inline void DLLA<elementType>::resize()
{
	this->capacity *= 2;
	DllaNode<elementType>* aux = new DllaNode<elementType>[this->capacity];
	for (int index = 0; index < this->capacity / 2; index++) {
		aux[index] = this->elements[index];
	}
	for (int index = capacity / 2; index < capacity; index++) {
		aux[index].next = index + 1;
		aux[index].prev = index - 1;
	}
	aux[capacity - 1].next = -1;
	firstEmpty = capacity / 2;
	this->elements = aux;
}
