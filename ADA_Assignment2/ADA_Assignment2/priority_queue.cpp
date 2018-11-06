#include "priority_queue.h"


priority_queue::priority_queue(bool lessthanIn, int init_length)
{
	array = new int[init_length];
	array_length = init_length;
	currentSize = 0;
	lessthan = lessthanIn;
}

priority_queue::~priority_queue()
{
	delete[] array;
}

void priority_queue::push(int value)
{
	if (currentSize == array_length - 1) enlargeArray(array_length * 2 + 1);

	int hole = ++currentSize;
	for ( ; hole > 1 && compere(value, array[hole/2]); hole /= 2)
	{
		array[hole] = array[hole / 2];
	}
	array[hole] = value;
}

void priority_queue::pop()
{
	if (not currentSize) return;
	array[1] = array[currentSize--];
	percolateDown(1);
}

int priority_queue::size()
{
	return currentSize;
}

bool priority_queue::empty()
{
	return currentSize == 0;
}

int priority_queue::top()
{
	return array[1];
}

void priority_queue::enlargeArray(int length)
{
	int *temp = new int[length];

	for (size_t i = 0; i < array_length; i++)
	{
		temp[i] = array[i];
	}

	delete[] array;

	array = temp;

	array_length = length;
}

void priority_queue::percolateDown(int hole)
{
	int child;
	int tmp = array[hole];

	for (; hole *2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize and compere(array[child + 1], array[child])) child++;
		if (compere(array[child], tmp)) array[hole] = array[child];
		else break;
	}
	array[hole] = tmp;
}

bool priority_queue::compere(int a, int b)
{
	if (lessthan) return a < b;
	else return a > b;
}
