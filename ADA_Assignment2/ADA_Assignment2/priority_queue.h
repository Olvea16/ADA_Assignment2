#pragma once
#include "Defs.h"

using namespace std;

struct PQSTimeComplexityStats {
	unsigned int nArrayAccesses = 0, nComparisons = 0;
};

class priority_queue
{
public:
	priority_queue(bool lessthanIn = true, int init_length = 50);
	~priority_queue();
	void push(arrayType value, PQSTimeComplexityStats& stats);
	void pop(PQSTimeComplexityStats& stats  );
	int size(PQSTimeComplexityStats& stats  );
	bool empty(PQSTimeComplexityStats& stats  );
	arrayType top(PQSTimeComplexityStats& stats  );
protected:
	arrayType* array;
	int array_length;
	int currentSize;
	void enlargeArray(int length, PQSTimeComplexityStats& stats  );
	void percolateDown(int hole, PQSTimeComplexityStats& stats  );
	bool lessthan;
	bool compare(arrayType a, arrayType b, PQSTimeComplexityStats& stats  );
};