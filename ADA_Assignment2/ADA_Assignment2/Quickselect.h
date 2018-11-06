#pragma once
#include "Defs.h"

#include <vector>


struct QSTimeComplexityStats {
	int nPointerIncrementations = 0, nSwaps = 0;
};

class Quickselect
{
public:
	Quickselect();
	~Quickselect();

	static double select(std::vector<arrayType> arr, int k, QSTimeComplexityStats& stats);
	static void partition(std::vector<arrayType>& arr, unsigned int& pivot, unsigned int left, unsigned int right, QSTimeComplexityStats& stats);
};

