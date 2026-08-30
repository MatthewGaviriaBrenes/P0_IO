#ifndef KNAPSACK_ITEM_H
#define KNAPSACK_ITEM_H

#include <stdlib.h>
#include <stdio.h>

typedef struct  {
    int value;
    int weight;
    int ratio; // Value/Ratio - Review if necessary.
    bool available;
} KnapsackItem;

typedef struct {
    int size;   // Store list size for easy access.
    KnapsackItem *items;
} KnapsackItemList;


// Function prototypes for knapsack item management. //

// Create a new knapsack item with specified value and weight.
KnapsackItem *create_knapsack_item(int value, int weight);

// Create an array to store a specific amount of items to fill the knapsack.
KnapsackItemList *new_knapsack_items_list(int listSize);

// Set value of knapsack item inside a list at a specific index. 
// If the index is out of bounds, print an error message.
void set_knapsack_item(KnapsackItemList *list, int index, int value, int weight, bool available);

// Get pointer to knapsack item in a list at a specific index.
// If the index is out of bounds or the list is NULL, print an error message and return NULL.
KnapsackItem* get_knapsack_item(KnapsackItemList *list, int index);

// Get the index of the most valuable item in the list up to a specified weight limit.
// Return -1 if no item is available; -2 if there is an error.
// If proportional is true, consider the value-to-weight ratio instead of just value.
int get_most_valuable_item_index(KnapsackItem *itemsList, int listSize, 
    int weightLimit, bool proportional);

// Create a random set of knapsack items with specified list size, maximum value, and maximum weight.
KnapsackItemList *create_random_knapsack_items_list(int listSize, int maxValue, int maxWeight);

// Free the memory allocated for the knapsack item list and its items.
// Use for memory cleanup after the knapsack problem is solved.
void free_knapsack_item_list(KnapsackItemList *list);

#endif