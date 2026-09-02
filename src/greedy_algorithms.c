// greedy_algorithms.c

#include "greedy_algorithms.h"


// Fill the knapsack using the Greedy algorithms.
// If proportional param is true, use ratio of value to weight for selection (Proportional Greedy).
// If proportional param is false, use value for selection (Simple Greedy).
void greedy_fill_knapsack(Knapsack *bag, ItemList *itemList, bool proportional) {
    if (bag == NULL || itemList == NULL) {
        fprintf(stderr, "Error: Knapsack bag or items list is NULL.\n");
        return;
    }
    if (itemList->size == 0) {
        fprintf(stderr, "Error: Items list is empty.\n");
        return;
    }
    if (bag->availableWeight <= 0) {
        fprintf(stderr, "Error: Knapsack bag has no available weight.\n");
        return;
    }
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
            add_item_to_knapsack(bag, bestItem);
        }
    }
    if (addedItemCount == 0) {
        fprintf(stderr, "Warning: No items were added to the knapsack. Knapsack may not have sufficient available capacity or there are no available items to add.\n");
    }
}

// Wrapper function to run Simple Greedy algorithm to fill the knapsack.
void simple_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList) {
    greedy_fill_knapsack(bag, itemList, false);
}

// Wrapper function to run Proportional Greedy algorithm to fill the knapsack.
void proportional_greedy_fill_knapsack(Knapsack *bag, ItemList *itemList) {
    greedy_fill_knapsack(bag, itemList, true);
}
