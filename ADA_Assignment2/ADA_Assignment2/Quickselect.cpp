#include "Quickselect.h"

void swap(std::vector<arrayType>& vec, unsigned int a, unsigned int b, QSTimeComplexityStats& stats) {
	stats.nSwaps++;
	std::iter_swap(vec.begin() + a, vec.begin() + b);
}

Quickselect::Quickselect()
{
}


Quickselect::~Quickselect()
{
}

double Quickselect::select(std::vector<arrayType> arr, int k, QSTimeComplexityStats& stats, bool oldVersion)
{
	arrayType result = 0;
	if (arr.size() < 1) return result;
	if (oldVersion) {
		k--;
		int left = 0, right = arr.size() - 1, pivot;
		while (true) {
			if (left == right) return arr[left];

			pivot = left + (right - left) / 2;

			if (arr[left] < arr[pivot]) {
				if (arr[left] < arr[right]) {
					if (arr[right] < arr[pivot]) pivot = right;
				}
				else if (arr[right] < arr[pivot]) pivot = right;
			}
			else if (arr[left] < arr[right]) pivot = left;
			else pivot = right;

			partition(arr, pivot, left, right, stats);

			if (pivot == k) {
				result = arr[k];
				break;
			}
			else if (pivot < k)  left = pivot + 1;
			else if (pivot > k)  right = pivot - 1;
		}
	}
	else {
		int l = 0, r = arr.size() - 1, pivot;
		if (k >= 0 && k < arr.size()) {
			partition(arr, pivot, l, r, stats);
			if (pivot == k) return arr[k];

			if (pivot > k) r = pivot - 1;
			else l = pivot + 1;
			return select(std::vector<arrayType>(arr.begin() + l, arr.begin() + r + 1), k - l, stats, oldVersion);
		}
		else return INT_MAX;
	}
	
	return result;
}

void Quickselect::partition(std::vector<arrayType>& arr, int& pivot, unsigned int left, unsigned int right, QSTimeComplexityStats & stats)
{
	arrayType value = arr[right];
	pivot = left;

	for (unsigned int i = left; i < right; i++) {
		if (arr[i] < value) {
			swap(arr, pivot, i, stats);
			pivot++;
		}
	}
	swap(arr, right, pivot, stats);
}
