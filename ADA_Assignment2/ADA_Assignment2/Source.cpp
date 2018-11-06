#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
using namespace std;

int randomInt(int maxVal = 100) {
	return rand() % maxVal;
}

void priority_queue_test() {
	srand(time(NULL));
	priority_queue te(false);
	for (int i = 0; i < 100; i++)
	{
		te.push(randomInt());
	}
	int dic = 0;
	int lastNumber = te.top();
	bool notSortet = false;
	for (int i = 0; i < 100; i++)
	{
		int top = te.top();

		int dicNew = dic;
		if (top - lastNumber != 0) dicNew = (top - lastNumber) / (abs(top - lastNumber));
		if (dic == 0) dic = dicNew;
		if (dic != dicNew) notSortet = true;

		lastNumber = top;
		cout << top << ", ";
		te.pop();
	}
	cout << endl << "Sortet: " << !notSortet << endl;
}

int main() {
	
	system("pause");
	return 0;
}

