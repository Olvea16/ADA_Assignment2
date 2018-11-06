#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "Json.h"
#include <math.h>

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
	bool notSorted = false;
	for (int i = 0; i < 100; i++)
	{
		int top = te.top();

		int dicNew = dic;
		if (top - lastNumber != 0) dicNew = (top - lastNumber) / (abs(top - lastNumber));
		if (dic == 0) dic = dicNew;
		if (dic != dicNew) notSorted = true;

		lastNumber = top;
		cout << top << ", ";
		te.pop();
	}
	cout << endl << "Sorted: " << !notSorted << endl;
}

int main() {
	vector<float> vecx, vecy;
	for (float i = 0; i < 10; i += 0.1)
	{
		vecx.push_back(i);
		vecy.push_back(cos(i));
	}
	makeJOSNPlotData("Test Plot", "n", "Time [ns]", vecx, vecy,"triplot");

	system("pause");
	return 0;
}

