// knapsack_run.h

#ifndef KNAPSACK_RUN_H
#define KNAPSACK_RUN_H

#include "knapsack_items.h"
#include "knapsack_bag.h"

// Structure to hold metadata about a knapsack run.
typedef struct {
    double executionTime;       // Execution time of generated knapsack in ms.
    Knapsack *bag;              // Pointer to generated knapsack bag.
} KnapsackRunResult;

// Print the result of a knapsack run on the screen.
void print_knapsack_run_result(const KnapsackRunResult *result);

//TODO: Add functions to output contents of knapsack run to TEX file.

#endif // KNAPSACK_RUN_H