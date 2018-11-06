#pragma once

using namespace std;

class priority_queue
{
public:
	priority_queue(bool lessthanIn = true, int init_length = 50);
	~priority_queue();
	void push(int value);
	void pop();
	int size();
	bool empty();
	int top();
protected:
	int* array;
	int array_length;
	int currentSize;
	void enlargeArray(int length);
	void percolateDown(int hole);
	bool lessthan;
	bool compere(int a, int b);
};