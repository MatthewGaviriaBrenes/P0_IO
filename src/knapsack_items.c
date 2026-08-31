#include "knapsack_items.h"

// Create a new knapsack item with specified value and weight.
Item *item_create(int value, int weight) {
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL) {
        fprintf(stderr, "Memory allocation failed for Item.\n");
        exit(EXIT_FAILURE);
    }
    item->value = value;
    item->weight = weight;
    item->ratio = (weight != 0) ? (value / weight) : 0; // Avoid division by zero.
    item->available = true; 
    return item;
}

// Create an array to store a specific amount of items to fill the knapsack.
ItemList *item_list_create(size_t listSize) {
    if (listSize <= 0) {
        fprintf(stderr, "Number of items must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }
    ItemList *list = (ItemList *)malloc(sizeof(ItemList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed for ItemList.\n");
        exit(EXIT_FAILURE);
    }
    list->size = listSize;
    list->items = (Item *)malloc(listSize * sizeof(Item));
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

// Free the memory allocated for the knapsack item list and its items.
// Use for memory cleanup after the knapsack problem is solved.
void item_list_free(const ItemList *list) {
    if (list == NULL) {
        return;
    }
    free(list->items);
    free((void *)list);
}

// Set value of knapsack item inside a list at a specific index. 
// If the index is out of bounds, print an error message.
void set_knapsack_item(const ItemList *list, size_t index, int value, int weight, bool available) {
    if (list == NULL) {
        fprintf(stderr, "Items list is NULL.\n");
        return;
    }
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index %zu is out of bounds for items list of size %zu.\n", index, list->size);
        return;
    }
    list->items[index].value = value;
    list->items[index].weight = weight;
    list->items[index].ratio = (weight != 0) ? (value / weight) : 0; // Avoid division by zero.
    list->items[index].available = available; 
}

// Get pointer to knapsack item in a list at a specific index.
// If the index is out of bounds or the list is NULL, print an error message and return NULL.
Item* get_knapsack_item(const ItemList *list, size_t index) {
    if (list == NULL) {
        fprintf(stderr, "Items list is NULL.\n");
        return NULL;
    } if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index %zu is out of bounds for items list of size %zu.\n", index, list->size);
        return NULL;
    }
    return &(list->items[index]);
}

// Get a pointer to the most valuable item in the list up to a specified weight limit.
// If proportional is true, consider the value-to-weight ratio instead of just value.
Item* get_most_valuable_item(const Item *itemsList, size_t listSize, int weightLimit, bool proportional) {
    if (itemsList == NULL || listSize <= 0) {
        fprintf(stderr, "Items list is NULL or size is invalid.\n");
        return NULL;
    } 
    if (weightLimit <= 0) {
        fprintf(stderr, "Weight limit must be greater than zero.\n");
        return NULL;
    }

    Item *bestItem = NULL; // Initialize to NULL to indicate no item found yet.
    int bestValue = 0; // Initialize to zero (raw value or value ratio of an item will never be zero).

    for (size_t index = 0; index < listSize; index++) {
        const Item *item = &itemsList[index];
        if (item->available && item->weight <= weightLimit) {
            int currentValue = proportional ? item->ratio : item->value;
            if (currentValue > bestValue) {
                bestValue = currentValue;
                bestItem = (Item *)item; // Cast to non-const pointer for return.
            } else if (currentValue == bestValue) {
                // If raw value (or value ratio) are equal, prefer the item with the lower weight.
                if (bestItem == NULL || item->weight < bestItem->weight) {
                    bestItem = (Item *)item; // Cast to non-const pointer for return.
                }
            }
        }
    }
    return bestItem;
}

// Get the index of the most valuable item in the list up to a specified weight limit.
// If proportional is true, consider the value-to-weight ratio instead of just value.
size_t get_most_valuable_item_index(const Item *itemsList, size_t listSize, 
    int weightLimit, bool proportional) {
    if (itemsList == NULL || listSize <= 0) {
        fprintf(stderr, "Items list is NULL or size is invalid.\n");
        return LIST_ERROR; // Error code for invalid list operations.
    } 
    if (weightLimit <= 0) {
        fprintf(stderr, "Weight limit must be greater than zero.\n");
        return LIST_ERROR; // Error code for invalid list operations.
    }

    size_t bestIndex = LIST_ERROR; // Initialize to an invalid index to indicate no item found yet.
    int bestValue = 0; // Initialize to zero (raw value or value ratio of an item will never be zero).

    for (size_t index = 0; index < listSize; index++) {
        const Item *item = &itemsList[index];
        if (item->available && item->weight <= weightLimit) {
            int currentValue = proportional ? item->ratio : item->value;
            if (currentValue > bestValue) {
                bestValue = currentValue;
                bestIndex = index;
            } else if (currentValue == bestValue) {
                // If raw value (or value ratio) are equal, prefer the item with the lower weight.
                if (item->weight < itemsList[bestIndex].weight) {
                    bestIndex = index;
                }
            }
        }
    }
    return bestIndex;
}

// Create a random set of knapsack items with specified list size, maximum value, and maximum weight.
ItemList *item_list_create_random(size_t listSize, int maxValue, int maxWeight) {
    if (listSize <= 0 || maxValue <= 0 || maxWeight <= 0) {
        fprintf(stderr, "List size, max value, and max weight must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }
    ItemList *list = item_list_create(listSize);
    for (size_t index = 0; index < listSize; index++) {
        int value = rand() % maxValue + 1; // Random value between 1 and maxValue.
        int weight = rand() % maxWeight + 1; // Random weight between 1 and maxWeight.
        set_knapsack_item(list, index, value, weight, true);
    }
    return list;
}

