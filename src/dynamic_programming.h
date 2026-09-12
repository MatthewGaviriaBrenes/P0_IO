// dynamic_programming.h
// 0/1 Knapsack solver using bottom-up Dynamic Programming.
// (Item / ItemList / Knapsack / KnapsackRunResult).

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <stdbool.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"

typedef struct {
    KnapsackRunResult result;  // executionTime (ms) + resulting filled bag.
    int **table;               // DP table, size rows x cols.
    int rows;                  // itemCount + 1
    int cols;                  // capacity + 1
} DPKnapsackResult;

DPKnapsackResult dp_knapsack_solve(Knapsack *bag, const ItemList *itemsList);

// Free the DP table stored inside a DPKnapsackResult.
// Does NOT free result.result.bag
void dp_result_free_table(DPKnapsackResult *dpResult);

// Print the DP table to stdout in a readable grid (rows = items considered, columns = capacity 0..W).
// The same 'table' field can be walked directly to build a LaTeX table instead.
void print_dp_table(const DPKnapsackResult *dpResult, const ItemList *itemsList);

#endif
