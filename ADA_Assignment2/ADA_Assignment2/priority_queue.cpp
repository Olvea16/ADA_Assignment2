#include "priority_queue.h"


priority_queue::priority_queue(bool lessthanIn, int init_length)
{
	array = new arrayType[init_length];
	array_length = init_length;
	currentSize = 0;
	lessthan = lessthanIn;
}

priority_queue::~priority_queue()
{
	delete[] array;
}

void priority_queue::push(arrayType value, PQSTimeComplexityStats& stats)
{
	if (currentSize == array_length - 1) enlargeArray(array_length * 2 + 1);

	int hole = ++currentSize;
	for ( ; hole > 1 && compare(value, array[hole/2]); hole /= 2)
	{
		array[hole] = array[hole / 2];
		stats.nArrayAccesses++;
	}
	array[hole] = value;
	stats.nArrayAccesses++;
}

void priority_queue::pop(PQSTimeComplexityStats& stats)
{
	if (not currentSize) return;
	array[1] = array[currentSize--];
	stats.nArrayAccesses++;
	percolateDown(1);
}

int priority_queue::size(PQSTimeComplexityStats& stats)
{
	return currentSize;
}

bool priority_queue::empty(PQSTimeComplexityStats& stats)
{
	return currentSize == 0;
}

arrayType priority_queue::top(PQSTimeComplexityStats& stats)
{
	return array[1];
	stats.nArrayAccesses++;
}

void priority_queue::enlargeArray(int length, PQSTimeComplexityStats& stats)
{
	arrayType *temp = new arrayType[length];

	for (size_t i = 0; i < array_length; i++)
	{
		temp[i] = array[i];
		stats.nArrayAccesses++;
	}

	delete[] array;

	array = temp;

	array_length = length;
}

void priority_queue::percolateDown(int hole, PQSTimeComplexityStats& stats)
{
	int child;
	int tmp = array[hole];
	stats.nArrayAccesses++;

	for (; hole *2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize and compare(array[child + 1], array[child])) child++;
		if (compare(array[child], tmp)) array[hole] = array[child];
		else break;
	}
	array[hole] = tmp;
}

bool priority_queue::compare(arrayType a, arrayType b, PQSTimeComplexityStats& stats)
{
	stats.nComparisons++;
	if (lessthan) return a < b;
	else return a > b;
}
