#pragma once
#include "Defs.h"
#include "priority_queue.h"

#include <vector>

struct PQSTimeComplexityStats {
	unsigned int nArrayAccesses, nComparisons;
};

class PriorityQueueSelect
{
public:
	PriorityQueueSelect();
	~PriorityQueueSelect();

	static arrayType select(std::vector<arrayType> arr, unsigned int k, PQSTimeComplexityStats& stats);
};

