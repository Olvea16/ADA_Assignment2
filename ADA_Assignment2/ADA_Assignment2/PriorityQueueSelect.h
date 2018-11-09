#pragma once
#include "Defs.h"
#include "priority_queue.h"

#include <vector>


class PriorityQueueSelect
{
public:
	PriorityQueueSelect();
	~PriorityQueueSelect();

	static arrayType select(std::vector<arrayType> arr, unsigned int k, PQSTimeComplexityStats& stats);
};

