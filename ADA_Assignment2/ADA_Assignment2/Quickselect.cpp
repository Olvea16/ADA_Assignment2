#include "Quickselect.h"

void swap(std::vector<arrayType>& vec, unsigned int a, unsigned int b, QSTimeComplexityStats& stats) {
	double temp = vec[a];
	vec[a] = vec[b];
	vec[b] = temp;
	stats.nSwaps++;
}

Quickselect::Quickselect()
{
}


Quickselect::~Quickselect()
{
}

double Quickselect::select(std::vector<arrayType> arr, int k, QSTimeComplexityStats& stats)
{
	arrayType result = 0;
	k--;
	unsigned int left = 0, right = arr.size() - 1, pivot;
	while (true) {
		if (left == right) return arr[left];

		pivot = left + rand() % (right - left - 1) + 1;
		partition(arr, pivot, left, right, stats);

		if (pivot == k) {
			result = arr[k];
			break;
		}
		else if (pivot < k)  left = pivot +	1;
		else if (pivot > k)  right = pivot - 1;
	}
	return result;
}

void Quickselect::partition(std::vector<arrayType>& arr, unsigned int& pivot, unsigned int left, unsigned int right, QSTimeComplexityStats & stats)
{
	arrayType value = arr[pivot];
	swap(arr, pivot, right, stats);
	pivot = left;

	for (unsigned int i = left; i < right; i++) {
		if (arr[i] < value) {
			swap(arr, pivot, i, stats);
			pivot++;
		}
	}
	swap(arr, right, pivot, stats);
}
