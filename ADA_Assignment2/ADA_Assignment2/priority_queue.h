#pragma once
#include "Defs.h"

using namespace std;

struct PQSTimeComplexityStats {
	unsigned int nArrayAccesses = 0, nComparisons = 0;
} pqstNull;

class priority_queue
{
public:
	priority_queue(bool lessthanIn = true, int init_length = 50);
	~priority_queue();
	void push(arrayType value, PQSTimeComplexityStats& stats = pqstNull);
	void pop(PQSTimeComplexityStats& stats = pqstNull);
	int size(PQSTimeComplexityStats& stats = pqstNull);
	bool empty(PQSTimeComplexityStats& stats = pqstNull);
	arrayType top(PQSTimeComplexityStats& stats = pqstNull);
protected:
	arrayType* array;
	int array_length;
	int currentSize;
	void enlargeArray(int length, PQSTimeComplexityStats& stats = pqstNull);
	void percolateDown(int hole, PQSTimeComplexityStats& stats = pqstNull);
	bool lessthan;
	bool compare(arrayType a, arrayType b, PQSTimeComplexityStats& stats = pqstNull);
};