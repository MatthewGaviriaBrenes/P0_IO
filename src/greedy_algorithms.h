// greedy_algorithms.h

#include <time.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"

#ifndef GREEDY_ALGORITHMS_H
#define GREEDY_ALGORITHMS_H


// Fill the knapsack using the Greedy algorithms.
// If proportional param is true, use ratio of value to weight for selection (Proportional Greedy).
// If proportional param is false, use value for selection (Simple Greedy).
// Returns a KnapsackRun structure containing the execution time and a pointer to the filled knapsack bag.
KnapsackRun greedy_fill_knapsack(Knapsack *bag, ItemList *itemList, bool proportional);

// Wrapper function to run Simple Greedy algorithm (use raw value for selection).
KnapsackRun simple_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList);

// Wrapper function to run Proportional Greedy algorithm (use value-to-weight ratio for selection).
KnapsackRun proportional_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList);


#endif // GREEDY_ALGORITHMS_H