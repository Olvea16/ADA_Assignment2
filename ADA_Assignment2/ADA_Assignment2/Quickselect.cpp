#include "Quickselect.h"
Quickselect::Quickselect()
{
}


Quickselect::~Quickselect()
{
}

void swap(std::vector<arrayType>& vec, unsigned int a, unsigned int b, QSTimeComplexityStats& stats) {
	stats.nSwaps++;
	std::iter_swap(vec.begin() + a, vec.begin() + b);
}

double Quickselect::select(std::vector<arrayType> arr, int k, QSTimeComplexityStats& stats)
{
	int l = 0, r = arr.size() - 1, pivot;
	if (k >= 0 && k < arr.size()) {
		partition(arr, pivot, l, r, stats);
		if (pivot == k) return arr[k];

		if (pivot > k) {
			r = pivot - 1;
			stats.nPointerIncrementations++;
		}
		else {
			l = pivot + 1;
			stats.nPointerIncrementations++;
		}
		return select(std::vector<arrayType>(arr.begin() + l, arr.begin() + r + 1), k - l, stats);
	}
	else return INT_MAX;
	
}

void Quickselect::partition(std::vector<arrayType>& arr, int& pivot, unsigned int left, unsigned int right, QSTimeComplexityStats & stats)
{
	arrayType value = arr[right];
	pivot = left;
	stats.nPointerIncrementations++;

	for (unsigned int i = left; i < right; i++) {
		if (arr[i] < value) {
			swap(arr, pivot, i, stats);
			pivot++;
			stats.nPointerIncrementations++;
		}
		stats.nPointerIncrementations++;
	}
	swap(arr, right, pivot, stats);
}
