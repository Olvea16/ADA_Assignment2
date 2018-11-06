#pragma once
#include "Defs.h"

#include <vector>

struct PQSTimeComplexityStats {
	unsigned int nArrayAccesses, nComparisons;
};

class PriorityQueueSelect
{
public:
	PriorityQueueSelect();
	~PriorityQueueSelect();

	arrayType select(std::vector<arrayType> arr, unsigned int k);

	static double 
};

