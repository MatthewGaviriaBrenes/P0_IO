// experimental_mode.h
#include <stddef.h>
#include <time.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"
#include "greedy_algorithms.h"

#ifndef EXPERIMENTAL_MODE_H
#define EXPERIMENTAL_MODE_H

// Values for the start, end and steps for Knapsack weight capacity.
extern const int EXP_START_KNAPSACK_WEIGHT_CAPACITY;
extern const int EXP_END_KNAPSACK_WEIGHT_CAPACITY;
extern const int EXP_STEP_KNAPSACK_WEIGHT_CAPACITY;

// Values for the start, end and step values for Item county.
extern const size_t EXP_START_ITEM_COUNT;
extern const size_t EXP_END_ITEM_COUNT;
extern const size_t EXP_STEP_ITEM_COUNT;

// Max value for each item when generating random item lists in Experimental mode.
extern const int EXP_ITEM_MAX_VALUE;

typedef struct {
    double dynamicProgrammingTime, simpleGreedyTime, proportionalGreedyTime, simpleGreedyAccuracy, proportionalGreedyAccuracy;
} ExperimentResult;

// Run the simple greedy algorithm for a specific knapsack case in Experimental mode.
// Return NULL to indicate failure.
KnapsackRun *exp_run_sgAlgorithm(int knapsackMaxWeight, ItemList *itemList);

// Run the proportional greedy algorithm for a specific knapsack case in Experimental mode.3
// Return NULL to indicate failure.
KnapsackRun *exp_run_pgAlgorithm(int knapsackMaxWeight, ItemList *itemList);

// Run the specific knapsack case, including random generation of items and using it 
// Generates the random list of items and uses it to 
ExperimentResult run_exp_case_group(size_t caseCount, int knapsackMaxWeight, size_t itemCount);

// Run the experimental mode.
// Uses the number argument *n) passed by the "-E=n" parameter.
// For each case group from 1 to n, run 100 cases with varying item and weight capacities.
void run_exp_mode(size_t caseGroups);


#endif // EXPERIMENTAL_MODE_H