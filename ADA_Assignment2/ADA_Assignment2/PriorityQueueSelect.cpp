#include "PriorityQueueSelect.h"

PriorityQueueSelect::PriorityQueueSelect()
{
}


PriorityQueueSelect::~PriorityQueueSelect()
{
}

arrayType PriorityQueueSelect::select(std::vector<arrayType> arr, unsigned int k, PQSTimeComplexityStats & stats, unsigned long int statSize)
{
	priority_queue queue(true, statSize);
	for (arrayType n : arr) queue.push(n, stats);
	for (int i = k - 1; k > 1; k--) queue.pop(stats);
	return queue.top(stats);
}
