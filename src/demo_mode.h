// demo_run.h

#include <time.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"
#include "greedy_algorithms.h"

#ifndef DEMO_MODE_H
#define DEMO_MODE_H

// Maximum capacity of the knapsack and item count for demo mode.
extern const int DEMO_MAX_KNAPSACK_CAPACITY;

// Constraints for item list for demo mode.
extern const int DEMO_MAX_ITEMS;
extern const int DEMO_MAX_ITEM_VALUE;
extern const int DEMO_MAX_ITEM_WEIGHT;


// Run the demo mode.
void run_demo_mode();



#endif // DEMO_MODE_H