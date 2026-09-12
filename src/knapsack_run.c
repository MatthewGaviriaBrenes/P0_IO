// knapsack_run.c

#include "knapsack_run.h"

// Create knapsack run result with given execution time (ms) and knapsack bag in heap.
KnapsackRun *knapsack_run_create(double executionTime, Knapsack *bag) {
    if (bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag is NULL.\n");
        return NULL;
    }
    KnapsackRun *result = malloc(sizeof(KnapsackRun));
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for knapsack run result.\n");
        return NULL;
    }
    result->executionTime = executionTime;
    result->bag = bag;
    return result;
}

// Free the memory allocated for a knapsack run result.
// Also frees the knapsack bag in the run result.
void knapsack_run_free(KnapsackRun *result) {
    if (result == NULL) {
        return;
    }
    if (result->bag != NULL) {
        knapsack_free(result->bag);
        result->bag = NULL;
    }
    free(result);
}

// Print the result of a knapsack run on the screen.
void print_knapsack_run(const KnapsackRun *result) {
    if (result == NULL) {
        fprintf(stderr, "Error: Knapsack run result is NULL.\n");
        return;
    }
    
    printf("Knapsack Run Result:\n");
    printf("Execution Time: %.5f ms\n", result->executionTime);
    if (result->bag != NULL) {
        printf("Knapsack Bag - Max Capacity: %d, Available Capacity: %d, Item Count: %ld\n",
               result->bag->maxWeight, result->bag->freeWeight, result->bag->itemCount);
        
        for (int index = 0; index < result->bag->itemCount; index++) {
            Item *item = get_item_from_knapsack(result->bag, index);
            if (item != NULL) {
                printf("Id: %d, Value: %d, Weight: %d, Value-to-Weight-Ratio: %f\n"
                    , item->id, item->value, item->weight, get_item_ratio(item));
            } 
        }
        int totalItemWeight = result->bag->maxWeight - result->bag->freeWeight;
        printf("Total Item Value: %d, Total Item Weight: %d\n\n", result->bag->totalValue, totalItemWeight);
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
// Returns pointer to the newly added entry, or NULL if there were errors.
KnapsackRun *knapsack_run_list_add_entry(KnapsackRunList *log, KnapsackRun newEntry) {
    if (log == NULL) {
        fprintf(stderr, "Error: Knapsack run list is NULL.\n");
        return NULL;
    }
    if (log->count >= log->size) {
        fprintf(stderr, "Error: Knapsack run list is full. Cannot add new entry.\n");
        return NULL;
    }
    log->runs[log->count] = newEntry;
    log->count++;
    return &log->runs[log->count - 1];
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
double get_knapsack_runs_match_ratio(const KnapsackRunList *baseline, const KnapsackRunList *comparison) {
    if (baseline == NULL || comparison == NULL) {
        fprintf(stderr, "Error: One or both knapsack run lists are NULL. Defaulting to 0.\n");
        return 0.0;
    }
    if (baseline->count == 0 || comparison->count == 0) {
        fprintf(stderr, "Error: One or both knapsack run lists are empty. Defaulting to 0.\n");
        return 0.0;
    }
    if (baseline->count != comparison->count) {
        fprintf(stderr, "Warning: Knapsack run lists have different counts. Ratio will be 0.\n");
        return 0.0;
    }

    size_t matchingRuns = 0;     // Counter for matches.

    for (size_t count = 0; count < baseline->count; count++) {
        if (baseline->runs[count].bag != NULL && comparison->runs[count].bag != NULL) {
            if (baseline->runs[count].bag->totalValue == comparison->runs[count].bag->totalValue) {
                matchingRuns++;
            }
        }
        // If either run entry for either bag is NULL somehow, assume mismatch.
    }

    return (double)matchingRuns / (double)baseline->count;
}