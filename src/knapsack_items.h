#ifndef KNAPSACK_ITEM_H
#define KNAPSACK_ITEM_H

#include <stdlib.h>
#include <stdio.h>

#define LIST_ERROR ((size_t)-1) // Error code for invalid list operations.

typedef struct  {
    int value;
    int weight;
    int ratio; // Value/Ratio - Review if necessary.
    bool available;
} Item;


typedef struct {
    size_t size;   // Store list size for easy access.
    Item *items;
} ItemList;


// Function prototypes for knapsack item management. //

// Create a new knapsack item with specified value and weight.
Item *item_create(int value, int weight);

// Create an array to store a specific amount of items to fill the knapsack.
ItemList *item_list_create(size_t listSize);

// Free the memory allocated for the knapsack item list and its items.
// Use for memory cleanup after the knapsack problem is solved.
void item_list_free(const ItemList *list);

// Set value of knapsack item inside a list at a specific index. 
// If the index is out of bounds, print an error message.
void set_knapsack_item(const ItemList *list, size_t index, int value, int weight, bool available);

// Get pointer to knapsack item in a list at a specific index.
// If the index is out of bounds or the list is NULL, print an error message and return NULL.
Item* get_knapsack_item(const ItemList *list, size_t index);

// Get a pointer to the most valuable item in the list up to a specified weight limit.
// If proportional is true, consider the value-to-weight ratio instead of just value.
Item* get_most_valuable_item(const Item *itemsList, size_t listSize, int weightLimit, bool proportional);

// Get the index of the most valuable item in the list up to a specified weight limit.
// If proportional parameter is true, consider the value-to-weight ratio instead of just value.
size_t get_most_valuable_item_index(const Item *itemsList, size_t listSize, 
    int weightLimit, bool proportional);

// Create a random set of knapsack items with specified list size, maximum value, and maximum weight.
ItemList *item_list_create_random(size_t listSize, int maxValue, int maxWeight);

// Reset the available status of all items in the items list to true, making them available for selection again.
// Only use this function if using the same items list for multiple knapsack problem runs.
void reset_item_availability(ItemList *list);

#endif