#pragma once
#include "Defs.h"

using namespace std;

class priority_queue
{
public:
	priority_queue(bool lessthanIn = true, int init_length = 50);
	~priority_queue();
	void push(arrayType value);
	void pop();
	int size();
	bool empty();
	arrayType top();
protected:
	arrayType* array;
	int array_length;
	int currentSize;
	void enlargeArray(int length);
	void percolateDown(int hole);
	bool lessthan;
	bool compere(arrayType a, arrayType b);
};