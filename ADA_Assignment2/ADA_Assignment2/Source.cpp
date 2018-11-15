#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "Quickselect.h"
#include "PriorityQueueSelect.h"
#include "Json.h"
#include <math.h>
#include <random>

#include "Stopwatch.h"
#include "ConsoleMatrix.h"
#include "JSONPlot.h"

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
	PQSTimeComplexityStats stats;
	srand(time(NULL));
	priority_queue te(false);
	for (int i = 0; i < 100; i++)
	{
		te.push(randomInt(), stats);
	}
	int dic = 0;
	int lastNumber = te.top(stats);
	bool notSorted = false;
	for (int i = 0; i < 100; i++)
	{
		int top = te.top(stats);

		int dicNew = dic;
		if (top - lastNumber != 0) dicNew = (top - lastNumber) / (abs(top - lastNumber));
		if (dic == 0) dic = dicNew;
		if (dic != dicNew) notSorted = true;

		lastNumber = top;
		cout << top << ", ";
		te.pop(stats);
	}
	cout << endl << "Sorted: " << !notSorted << endl;
}

template < typename Iterator, typename Comparator>
void insertionSort(const Iterator & begin, const Iterator & end, Comparator lessThan)
	{
		if (begin == end)
			return;
	
		Iterator j;
	
		for (Iterator p = begin + 1; p != end; ++p)
		{
			auto tmp = std::move(*p);
			for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
				* j = std::move(*(j - 1));
			* j = std::move(tmp);
		}
	}

template < typename Iterator>
void insertionSort(const Iterator & begin, const Iterator & end)
{
	insertionSort(begin, end, less<decltype(*begin)>{ });
}

template < typename Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
	int center = (left + right) / 2;

	if (a[center] < a[left])
		std::swap(a[left], a[center]);
	if (a[right] < a[left])
		std::swap(a[left], a[right]);
	if (a[right] < a[center])
		std::swap(a[center], a[right]);

	// Place pivot at position right - 1
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

template < typename Comparable>
void quickSelect(vector<Comparable> & a, int left, int right, int k)
{
	if (left + 10 <= right)
		{
		const Comparable & pivot = median3(a, left, right);
		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
			{
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
			}
			std::swap(a[i], a[right - 1]); // Restore pivot
			
										   // Recurse; only this part changes
			if (k <= i)
				quickSelect(a, left, i - 1, k);
			else if (k > i + 1)
				quickSelect(a, i + 1, right, k);
		}
	else // Do an insertion sort on the subarray
		insertionSort(a.begin() + left, a.begin() + right);
}

std::vector<float> getAvg(std::vector <std::vector<float>> vec) {
	std::vector<float> sum;
	for (size_t i = 0; i < vec.size(); i++) {
		sum.push_back(0.0);
		for (size_t j = 0; j < vec.at(i).size(); j++)
		{
			sum.at(i) += vec.at(i).at(j);
		}
		sum.at(i) /= vec.at(i).size();
	}
	return sum;
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
	std::vector<float> xdata;

	std::vector <std::vector<float>> ydata_qstats_nPointerIncrementations;
	std::vector <std::vector<float>> ydata_qstats_nSwaps;
	std::vector <std::vector<float>> ydata_pqstats_nArrayAccesses;
	std::vector <std::vector<float>> ydata_pqstats_nComparisons;
	int maxN = 100000;
	int k = 9;

	std::vector<int> ns;
	for (int N = 10; N < maxN; N *= sqrt(10))
	{
		ns.push_back(N);
	}

	for (int i = 0; i < ns.size(); i++)//
	{
		int N = ns.at(i);
		xdata.push_back(N);
		ydata_qstats_nPointerIncrementations.push_back(std::vector<float>());
		ydata_qstats_nSwaps.push_back(std::vector<float>());
		ydata_pqstats_nArrayAccesses.push_back(std::vector<float>());
		ydata_pqstats_nComparisons.push_back(std::vector<float>());

		std::cout << N << " -- " << ((i + 1.0) / ns.size()) * 100 << "%" << endl;

		std::vector<arrayType> vec(N);
		for (int g = 0; g < N; g++) vec[g] = (N - g);
		
		int nK = 100;
		for (int j = 0; j < nK; j++)
		{
			
			k = 1 + randomInt(N - 2);
			std::cout << '\t' << k << " -- " << ((j) / float(nK)) * 100 << "%" << endl;

			random_shuffle(vec.begin(), vec.end());

			QSTimeComplexityStats qstats;
			PQSTimeComplexityStats pqstats;

			double nqsVal = Quickselect::select(vec, k - 1, qstats);

			double pqsVal = PriorityQueueSelect::select(vec, k, pqstats);


			ydata_qstats_nPointerIncrementations.back().push_back(qstats.nPointerIncrementations);
			ydata_qstats_nSwaps.back().push_back(qstats.nSwaps);
			ydata_pqstats_nArrayAccesses.back().push_back(pqstats.nArrayAccesses);
			ydata_pqstats_nComparisons.back().push_back(pqstats.nComparisons);
		}
	}




	JSONPlot jp("Complexity","N","times");
	jp.addData("qstats_nPointerIncrementations", xdata, getAvg(ydata_qstats_nPointerIncrementations));
	jp.addData("qstats_nSwaps", xdata, getAvg(ydata_qstats_nSwaps));
	jp.addData("pqstats_nArrayAccesses", xdata, getAvg(ydata_pqstats_nArrayAccesses));
	jp.addData("pqstats_nComparisons", xdata, getAvg(ydata_pqstats_nComparisons));
	jp.write();

	std::system("pause");
	return 0;
}
