#ifndef KNAPSACK_BAG_H
#define KNAPSACK_BAG_H

#include <stdlib.h>
#include <stdio.h>

#include "knapsack_items.h"


typedef struct {
    int maxWeight;
    int availableWeight;
    int totalValue;         // Total value of items in the knapsack.    
    int itemCount;          // Counts items in Knapsack, also serves as index for next item to be added.
    int itemCapacity;       // Capacity of the items array, used for memory management.
    Item **items;       // Items chosen to fill the knapsack. Uses array of pointers to items to reuse items from the available items list.
} Knapsack;

// Create a new knapsack with specified maximum weight and item capacity.
// Item capacity is used for memory management of array used to store items.
// Hint: Use size of available items to set knapsack's item capacity. 
Knapsack *knapsack_create(int maxWeight, int itemCapacity);

// Free the memory allocated for the knapsack bag.
// Items used by the knapsack are not freed here, as they can be reused for other knapsack problem runs.
// They should be freed separately if not needed anymore.
void knapsack_free(Knapsack *bag);

// Add an item to the knapsack, updating available weight and item count.
// Counter for current items in knapsack also serves as index for new item.
// Returns pointer to item if it could be added.
// Return NULL if item could not be added (e.g., due to weight constraints).
Item *add_item_to_knapsack(Knapsack *bag, Item *item);

// Get an item from the knapsack by index.
// Returns NULL pointer if index is out of bounds (e.g. no item at that index) 
// or if the knapsack doesn't exist (NULL pointer).
Item *get_item_from_knapsack(const Knapsack *bag, int index);

// Reallocate the knapsack's items' array to a new capacity, preserving existing items.
// May not be needed, but it's there in case the items array has to accommodate more items.
// May not need it, but it's there just in case.
void expand_knapsack_item_capacity(Knapsack *bag, int newCapacity);

// Check if an item is already in the knapsack to avoid adding duplicates.
//TODO: Review if need to remove (for non-binary knapsack problem, duplicates may be allowed).
bool is_item_already_in_knapsack(const Knapsack *bag, const Item *item);

#endif