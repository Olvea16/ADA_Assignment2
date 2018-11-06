#pragma once

#include <vector>


struct QSTimeComplexityStats {
	int nPointerIncrementations = 0, nSwaps = 0;
};

class Quickselect
{
public:
	Quickselect();
	~Quickselect();

	static double select(std::vector<double> arr, int k, QSTimeComplexityStats& stats);
	static void partition(std::vector<double>& arr, unsigned int& pivot, unsigned int left, unsigned int right, QSTimeComplexityStats& stats);
};

