#ifndef KNAPSACK_BAG_H
#define KNAPSACK_BAG_H

#include <stdlib.h>
#include <stdio.h>

#include "knapsack_items.h"


// Note: itemCapacity has no effect on resolution of the knapsack problem
// It is necessary for memory management when adding items to the knapsack.
typedef struct {
    int maxWeight;
    int availableWeight;
    int itemCount;
    int itemCapacity;   
    Item **items;
} Knapsack;

// Create a new knapsack with specified maximum weight and item capacity.
// Item capacity is used for memory management of array used to store items.
// Hint: Use size of available items to set knapsack's item capacity. 
Knapsack *knapsack_create(int maxWeight, int itemCapacity);

// Free the memory allocated for the knapsack bag and its items.
void knapsack_free(const Knapsack *bag);

// Add an item to the knapsack, updating available weight and item count.
void add_item_to_knapsack(Knapsack *bag, Item *item);

// Get an item from the knapsack by index.
Item *get_item_from_knapsack(const Knapsack *bag, int index);

// Reallocate the knapsack's items' array to a new capacity, preserving existing items.
// May not be needed, but it's there in case the items array has to accommodate more items.
// May not need it, but it's there just in case.
void expand_knapsack_item_capacity(Knapsack *bag, int newCapacity);




#endif