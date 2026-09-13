// knapsack_run.c

#include "knapsack_run.h"

// Create knapsack run result with given execution time (ms) and knapsack bag in heap.
KnapsackRun knapsack_run_create(double executionTime, Knapsack *bag) {

    // Initialize result structure to hold execution time and pointer to the filled knapsack bag.
    KnapsackRun result = {0};

    if (bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag is NULL.\n");
    } else {
        result.executionTime = executionTime;
        result.bag = bag;
    }
    return result;
}

// Print the result of a knapsack run on the screen.
void print_knapsack_run(KnapsackRun result) {
    if (result.bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag in run result is NULL.\n");
        return;
    }    
    printf("Knapsack Run Result:\n");
    printf("Execution Time: %.6f ms\n", result.executionTime);
    if (result.bag != NULL) {
        printf("Knapsack Bag - Max Capacity: %d, Available Capacity: %d, Item Count: %ld\n",
               result.bag->maxWeight, result.bag->freeWeight, result.bag->itemCount);
        
        for (int index = 0; index < result.bag->itemCount; index++) {
            Item *item = get_item_from_knapsack(result.bag, index);
            if (item != NULL) {
                printf("Id: %d, Value: %d, Weight: %d, Value-to-Weight-Ratio: %f\n"
                    , item->id, item->value, item->weight, get_item_ratio(item));
            } 
        }
        int totalItemWeight = result.bag->maxWeight - result.bag->freeWeight;
        printf("Total Item Value: %d, Total Item Weight: %d\n\n", result.bag->totalValue, totalItemWeight);
    } else {
        printf("Knapsack Bag is NULL.\n");
    }
}

// Create a new list to store Knapsack run results.
KnapsackRunList *knapsack_run_list_create(size_t listSize) {
    if (listSize == 0) {
        fprintf(stderr, "Error: List size must be greater than 0.\n");
        return NULL;
    }
    KnapsackRunList *list = malloc(sizeof(KnapsackRunList));
    if (list == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for knapsack run list.\n");
        return NULL;
    }
    list->runs = malloc(listSize * sizeof(KnapsackRun));
    if (list->runs == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for knapsack run entries.\n");
        free(list);
        return NULL;
    }
    list->size = listSize;
    list->count = 0;
    return list;
}

// Free the knapsack run result list and its contents.
// Also frees the knapsack bags in each run result.
void knapsack_run_list_free(KnapsackRunList *log) {
    if (log == NULL) {
        return;
    }
    for (size_t index = 0; index < log->count; index++) {
        knapsack_free(log->runs[index].bag);
        log->runs[index].bag = NULL;
    }
    free(log->runs);
    free(log);
}

// Add a new Knapsack run result entry to a Knapasck Run list.
// Returns true if the entry was added successfully, false otherwise.
bool knapsack_run_list_add_entry(KnapsackRunList *log, KnapsackRun newEntry) {
    if (log == NULL) {
        fprintf(stderr, "Error: Knapsack run list is NULL.\n");
        return false;
    }
    if (log->count >= log->size) {
        fprintf(stderr, "Error: Knapsack run list is full. Cannot add new entry.\n");
        return false;
    }
    log->runs[log->count] = newEntry;
    log->count++;
    return true;
}

// Get the results of a knapsack run from a list in a given index.
// Returns NULL if the index is out of bounds or if the list is NULL.
KnapsackRun *get_knapsack_run_result(const KnapsackRunList *log, size_t index) {
    if (log == NULL) {
        fprintf(stderr, "Error: Knapsack run list is NULL.\n");
        return NULL;
    }
    if (index >= log->count) {
        fprintf(stderr, "Error: Index %zu is out of bounds for knapsack run list of size %zu.\n", index, log->count);
        return NULL;
    }
    return &log->runs[index];
}

// Get the average execution time of all knapsack runs in a list.
// Returns -1.0 if the list is NULL or empty (error state).
double get_knapsack_run_avg_execution_time(const KnapsackRunList *log) {
    if (log == NULL || log->count == 0) {
        fprintf(stderr, "Error: Knapsack run list is NULL or empty.\n");
        return -1.0;
    }
    double totalExecutionTime = 0.0;
    for (size_t index = 0; index < log->count; index++) {
        totalExecutionTime += log->runs[index].executionTime;
    }
    return totalExecutionTime / log->count;
}

// Get the ratio of matching total values between two knapsack run lists.
// Values must match in the same order of runs in both lists to be considered a match.
// Default to 0 if the run counts are different, since they cannot be compared one-to-one.
// Returns a ratio between 0.0 and 1.0 for the number of matching runs.
double get_knapsack_runs_match_ratio(const KnapsackRunList *baselineRuns, const KnapsackRunList *comparisonRuns) {
    if (baselineRuns == NULL || comparisonRuns == NULL) {
        fprintf(stderr, "Error: One or both knapsack run lists are NULL. Defaulting to 0.\n");
        return 0.0;
    }
    if (baselineRuns->count == 0 || comparisonRuns->count == 0) {
        fprintf(stderr, "Error: One or both knapsack run lists are empty. Defaulting to 0.\n");
        return 0.0;
    }
    if (baselineRuns->count != comparisonRuns->count) {
        fprintf(stderr, "Warning: Knapsack run lists have different counts. Ratio will be 0.\n");
        return 0.0;
    }

    size_t matchingRuns = 0;     // Counter for matches.

    for (size_t count = 0; count < baselineRuns->count; count++) {
        if (baselineRuns->runs[count].bag != NULL && comparisonRuns->runs[count].bag != NULL) {
            if (baselineRuns->runs[count].bag->totalValue == comparisonRuns->runs[count].bag->totalValue) {
                matchingRuns++;
            }
        }
        // If either run entry for either bag is NULL somehow, assume mismatch.
    }
    return (double) matchingRuns / (double) baselineRuns->count;
}