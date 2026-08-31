// greedy_algorithms.h

#ifndef GREEDY_ALGORITHMS_H
#define GREEDY_ALGORITHMS_H

#include "knapsack_items.h"
#include "knapsack_bag.h"


// Fill the knapsack using the Greedy algorithms.
// If proportional param is true, use ratio of value to weight for selection (Proportional Greedy).
// If proportional param is false, use value for selection (Simple Greedy).
void greedy_fill_knapsack(Knapsack *bag, ItemList *itemList, bool proportional);

// Wrapper function to run Simple Greedy algorithm to fill the knapsack.
void simple_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList);

// Wrapper function to run Proportional Greedy algorithm to fill the knapsack.
void proportional_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList);


#endif