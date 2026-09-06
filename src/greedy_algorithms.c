// greedy_algorithms.c

#include "greedy_algorithms.h"


// Fill the knapsack using the Greedy algorithms.
// If proportional param is true, use ratio of value to weight for selection (Proportional Greedy).
// If proportional param is false, use value for selection (Simple Greedy).
// Returns a KnapsackRunResult structure containing the execution time and a pointer to the filled knapsack bag.
KnapsackRunResult greedy_fill_knapsack(Knapsack *bag, ItemList *itemList, bool proportional) {
    KnapsackRunResult result; // Structure to hold the result of the greedy algorithm run.
    
    if (bag == NULL || itemList == NULL) {
        fprintf(stderr, "Error: Knapsack bag or items list is NULL.\n");
        return result;
    }
    if (itemList->size == 0) {
        fprintf(stderr, "Error: Items list is empty.\n");
        return result;;
    }
    if (bag->availableWeight <= 0) {
        fprintf(stderr, "Error: Knapsack bag has no available weight.\n");
        return result;;
    }

    // Set the start time to measure execution time of the greedy algorithm.
    clock_t startTimer = clock();

    size_t addedItemCount = 0; // Counter for items added to the knapsack.
    while (bag->availableWeight > 0) {
        // Select best available item from the list based on the greedy criteria (value or value-to-weight ratio).
        Item *bestItem = get_most_valuable_item(itemList, bag->availableWeight, proportional);
        if (bestItem == NULL) {
            // No more items can be added due to weight constraints.
            break;
        }
        // If selected item is already in the knapsack, mark it as unavailable to avoid re-selction and continue to the next best item.
        if (is_item_already_in_knapsack(bag, bestItem)) {
            bestItem->available = false; 
            continue;
        }
        // Mark selected item as unavailable to avoid re-selection and add it to the knapsack.
        else {
            bestItem->available = false;
            Item *addedItem = add_item_to_knapsack(bag, bestItem);

            // If item was successfully added to the knapsack, increment the counter.
            if (addedItem != NULL) {
                addedItemCount++;
            } 
        }
    }

    // Calculate execution time of the greedy algorithm in ms (with decimals) and store it in the result structure.
    clock_t endTimer = clock();
    result.executionTime = ((double)(endTimer - startTimer)) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds.

    // Show error message if no items were added to the knapsack after the greedy selection process.
    if (addedItemCount == 0) {
        fprintf(stderr, "Warning: No items were added to the knapsack. Knapsack may not have sufficient available capacity or there are no available items to add.\n");
    }

    // Add a pointer to the bag in its current state and return the result.
    result.bag = bag;
    return result;
}

// Wrapper function to run Simple Greedy algorithm to fill the knapsack.
KnapsackRunResult simple_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList) {
    return greedy_fill_knapsack(bag, itemList, false);
}

// Wrapper function to run Proportional Greedy algorithm to fill the knapsack.
KnapsackRunResult proportional_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList) {
    return greedy_fill_knapsack(bag, itemList, true);
}
