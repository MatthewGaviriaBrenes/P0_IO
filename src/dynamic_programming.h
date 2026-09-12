// dynamic_programming.h
//
// 0/1 Knapsack solver using bottom-up Dynamic Programming.
// Follows the same conventions used by the rest of the project
// (Item / ItemList / Knapsack / KnapsackRunResult).

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <stdbool.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"

// Result of a 0/1 Knapsack Dynamic Programming run.
//
// Besides the usual KnapsackRunResult (execution time + the Knapsack bag
// filled with the chosen items), this also keeps the full DP table that was
// used to compute the solution, since the assignment requires that table to
// be reported (e.g. printed on screen or exported later to LaTeX).
//
// table[i][w] = best achievable value using only the first i items
//               (i = 0 .. itemCount) with a capacity of w
//               (w = 0 .. bag->maxWeight).
//
// table is a (rows x cols) matrix of ints, dynamically allocated as an
// array of row pointers (rows = itemCount + 1, cols = capacity + 1).
typedef struct {
    KnapsackRunResult result;  // executionTime (ms) + resulting filled bag.
    int **table;               // DP table, size rows x cols.
    int rows;                  // itemCount + 1
    int cols;                  // capacity + 1
} DPKnapsackResult;

// Solve the 0/1 Knapsack problem for the given bag/items using bottom-up
// Dynamic Programming.
//
// - 'bag' must already exist (its maxWeight defines the knapsack capacity)
//   and should be empty; on return it will contain the optimal subset of
//   items (added via add_item_to_knapsack), and bag->totalValue / freeWeight
//   will reflect the optimal solution.
// - 'itemsList' provides the candidate items. This function does not modify
//   the 'available' flag of the items (unlike the greedy algorithms), since
//   the DP recurrence considers every item exactly once regardless of that
//   flag.
//
// Returns a DPKnapsackResult with:
//   - result.executionTime : time (in milliseconds) spent building the DP
//                             table and reconstructing the solution.
//   - result.bag           : same pointer received in 'bag'.
//   - table/rows/cols       : the full DP table, ready to be printed or
//                             exported to LaTeX. Caller owns this memory and
//                             must release it with dp_result_free_table().
//
// On error (NULL bag/itemsList, negative capacity, allocation failure) an
// error message is printed to stderr and a DPKnapsackResult with table=NULL
// and executionTime=0 is returned.
DPKnapsackResult dp_knapsack_solve(Knapsack *bag, const ItemList *itemsList);

// Free the DP table stored inside a DPKnapsackResult.
// Does NOT free result.result.bag: ownership of the Knapsack bag stays with
// whoever created it (same convention as knapsack_free elsewhere).
void dp_result_free_table(DPKnapsackResult *dpResult);

// Print the DP table to stdout in a readable grid (rows = items considered,
// columns = capacity 0..W). Mainly for debugging / quick inspection; the
// same 'table' field can be walked directly to build a LaTeX table instead.
void print_dp_table(const DPKnapsackResult *dpResult, const ItemList *itemsList);

#endif // DYNAMIC_PROGRAMMING_H
