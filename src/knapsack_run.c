// knapsack_run.c

#include "knapsack_run.h"

// Print the result of a knapsack run on the screen.
void print_knapsack_run_result(const KnapsackRunResult *result) {
    if (result == NULL) {
        fprintf(stderr, "Error: Knapsack run result is NULL.\n");
        return;
    }
    
    printf("Knapsack Run Result:\n");
    printf("Execution Time: %.5f ms\n", result->executionTime);
    if (result->bag != NULL) {
        printf("Knapsack Bag - Max Capacity: %d, Available Capacity: %d, Item Count: %d\n",
               result->bag->maxWeight, result->bag->availableWeight, result->bag->itemCount);
        int totalItemValue = 0;
        int totalItemWeight = 0;
        for (int index = 0; index < result->bag->itemCount; index++) {
            Item *item = get_item_from_knapsack(result->bag, index);
            if (item != NULL) {
                printf("Id: %d, Value: %d, Weight: %d\n", item->id, item->value, item->weight);
                totalItemValue += item->value;
                totalItemWeight += item->weight;
            } 
        }
        printf("Total Item Value: %d, Total Item Weight: %d\n\n", totalItemValue, totalItemWeight);
    } else {
        printf("Knapsack Bag is NULL.\n");
    }
}