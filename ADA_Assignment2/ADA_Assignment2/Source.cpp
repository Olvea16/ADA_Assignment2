#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "Quickselect.h"
#include "PriorityQueueSelect.h"
#include "Json.h"
#include <math.h>

#include "Stopwatch.h"
#include "ConsoleMatrix.h"

// CPP program for implementation of QuickSelect 
using namespace std;

// Standard partition process of QuickSort(). 
// It considers the last element as pivot 
// and moves all smaller element to left of 
// it and greater elements to right 
int partition(std::vector<int> arr, int l, int r)
{
	int x = arr[r], i = l;
	for (int j = l; j <= r - 1; j++) {
		if (arr[j] <= x) {
			std::iter_swap(arr.begin() + i, arr.begin() + j);
			i++;
		}
	}
	std::iter_swap(arr.begin() + i, arr.begin() + r);
	return i;
}

// This function returns k'th smallest  
// element in arr[l..r] using QuickSort  
// based method.  ASSUMPTION: ALL ELEMENTS 
// IN ARR[] ARE DISTINCT 
int kthSmallest(std::vector<int> arr, int l, int r, int k)
{
	// If k is smaller than number of  
	// elements in array 
	if (k > 0 && k <= r - l + 1) {

		// Partition the array around last  
		// element and get position of pivot  
		// element in sorted array 
		int index = partition(arr, l, r);

		// If position is same as k 
		if (index - l == k - 1)
			return arr[index];

		// If position is more, recur  
		// for left subarray 
		if (index - l > k - 1)
			return kthSmallest(arr, l, index - 1, k);

		// Else recur for right subarray 
		return kthSmallest(arr, index + 1, r,
			k - index + l - 1);
	}

	// If k is more than number of  
	// elements in array 
	return INT_MAX;
}

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
	Stopwatch sw;
	std::string swName;
	ConsoleMatrix cM(3,3);

	/*
	vector<float> vecx, vecy;
	for (float i = 0; i < 10; i += 0.1)
	{
		vecx.push_back(i);
		vecy.push_back(cos(i));
	}
	makeJOSNPlotData("Test Plot", "n", "Time [ns]", vecx, vecy,"triplot");
	*/

	int N = 100000;
	std::vector<arrayType> vec(N);
	for (int i = 0; i < N; i++) vec[i] = (N - i);
	random_shuffle(vec.begin(), vec.end());

	QSTimeComplexityStats qstats;
	PQSTimeComplexityStats pqstats;

	int k = 57;

	cM.addRow({ "N:", to_string(N) });
	cM.addRow({ "k:", to_string(k) });
	cM.addRow({ "Method:","Found Value:","Time Taken:" });

	swName = "Quickselect (old)";
	sw.start(swName);
	double oqsVal = Quickselect::select(vec, k, qstats, true);
	sw.stop(swName);
	cM.addRow({ swName, to_string(oqsVal), sw.getString(swName) });

	swName = "Quickselect (new)";
	sw.start(swName);
	double nqsVal = Quickselect::select(vec, k - 1, qstats);
	sw.stop(swName);
	cM.addRow({ swName, to_string(nqsVal), sw.getString(swName) });

	swName = "Quickselect (interwebz)";
	sw.start(swName);
	double netProgramming = kthSmallest(vec, 0, vec.size() - 1, k - 2);
	sw.stop(swName);
	cM.addRow({ swName, to_string(netProgramming), sw.getString(swName) });

	swName = "Queueselect";
	sw.start(swName);
	double pqsVal = PriorityQueueSelect::select(vec, k, pqstats);
	sw.stop(swName);
	cM.addRow({swName, to_string(pqsVal), sw.getString(swName)});

	cM.print();

	system("pause");
	return 0;
}
