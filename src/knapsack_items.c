#include "knapsack_items.h"

// Create a new knapsack item with specified value and weight.
KnapsackItem *create_knapsack_item(int value, int weight) {
    KnapsackItem *item = (KnapsackItem *)malloc(sizeof(KnapsackItem));
    if (item == NULL) {
        fprintf(stderr, "Memory allocation failed for KnapsackItem.\n");
        exit(EXIT_FAILURE);
    }
    item->value = value;
    item->weight = weight;
    item->ratio = (weight != 0) ? (value / weight) : 0; // Avoid division by zero.
    item->available = true; 
    return item;
}

// Create an array to store a specific amount of items to fill the knapsack.
KnapsackItemList *new_knapsack_items_list(int listSize) {
    if (listSize <= 0) {
        fprintf(stderr, "Number of items must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }
    KnapsackItemList *list = (KnapsackItemList *)malloc(sizeof(KnapsackItemList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed for KnapsackItemList.\n");
        exit(EXIT_FAILURE);
    }
    list->size = listSize;
    list->items = (KnapsackItem *)malloc(listSize * sizeof(KnapsackItem));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed for items array.\n");
        free(list);
        exit(EXIT_FAILURE);
    }
    // Initialize all items in the list to default values.
    // Use other functions to initialize values later.
    for (int index = 0; index < listSize; index++) {
        list->items[index].value = 0;
        list->items[index].weight = 0;
        list->items[index].ratio = 0;
        list->items[index].available = true;
    }
}

// Set value of knapsack item inside a list at a specific index. 
// If the index is out of bounds, print an error message.
void set_knapsack_item(KnapsackItemList *list, int index, int value, int weight, bool available) {
    if (list == NULL) {
        fprintf(stderr, "Items list is NULL.\n");
        return;
    }
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index %d is out of bounds for items list of size %d.\n", index, list->size);
        return;
    }
    list->items[index].value = value;
    list->items[index].weight = weight;
    list->items[index].ratio = (weight != 0) ? (value / weight) : 0; // Avoid division by zero.
    list->items[index].available = available; 
}

// Get pointer to knapsack item in a list at a specific index.
// If the index is out of bounds or the list is NULL, print an error message and return NULL.
KnapsackItem* get_knapsack_item(KnapsackItemList *list, int index) {
    if (list == NULL) {
        fprintf(stderr, "Items list is NULL.\n");
        return NULL;
    } if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index %d is out of bounds for items list of size %d.\n", index, list->size);
        return NULL;
    }
    return &(list->items[index]);
}

// Get the index of the most valuable item in the list up to a specified weight limit.
// Return -1 if no item is available; -2 if there is an error.
// If proportional is true, consider the value-to-weight ratio instead of just value.
int get_most_valuable_item_index(KnapsackItem *itemsList, int listSize, 
    int weightLimit, bool proportional) {
    if (itemsList == NULL) {
        fprintf(stderr, "Items list is NULL.\n");
        return -2;
    } if (weightLimit <= 0) {
        fprintf(stderr, "Weight limit must be greater than zero.\n");
        return -2;
    } 

    int mostValuableIndex = -1;
    int highestValue = 0;     // Can be highest direct value or highest ratio value.
    
    for (int currentIndex = 0; currentIndex < listSize; currentIndex++) {
        if (itemsList[currentIndex].available && itemsList[currentIndex].weight <= weightLimit) {
            int currentValue = proportional ? itemsList[currentIndex].ratio : itemsList[currentIndex].value;
            if (currentValue > highestValue) {
                highestValue = currentValue;
                mostValuableIndex = currentIndex;
            } if (currentValue == highestValue && mostValuableIndex != -1) {
                // If values are equal, prefer the item with the lower weight.
                if (itemsList[currentIndex].weight < itemsList[mostValuableIndex].weight) {
                    mostValuableIndex = currentIndex;
                }
            }
        }
    }
    return mostValuableIndex;
}

// Create a random set of knapsack items with specified list size, maximum value, and maximum weight.
KnapsackItemList *create_random_knapsack_items_list(int listSize, int maxValue, int maxWeight) {
    if (listSize <= 0 || maxValue <= 0 || maxWeight <= 0) {
        fprintf(stderr, "List size, max value, and max weight must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }
    KnapsackItemList *list = new_knapsack_items_list(listSize);
    for (int index = 0; index < listSize; index++) {
        int value = rand() % (maxValue + 1) + 1; // Random value between 1 and maxValue.
        int weight = rand() % (maxWeight + 1) + 1; // Random weight between 1 and maxWeight.
        set_knapsack_item(list, index, value, weight, true);
    }
    return list;
}

// Free the memory allocated for the knapsack item list and its items.
// Use for memory cleanup after the knapsack problem is solved.
void free_knapsack_item_list(KnapsackItemList *list) {
    if (list == NULL) {
        return;
    }
    free(list->items);
    free(list);
}
