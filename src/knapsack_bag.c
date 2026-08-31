#include "knapsack_bag.h"

// Create a new knapsack with specified maximum weight and item capacity.
// Item capacity is used for memory management of array used to store items.
// Hint: Use size of available items to set knapsack's item capacity. 
Knapsack *knapsack_create(int maxWeight, int itemCapacity) {
    Knapsack *bag = malloc(sizeof(Knapsack));
    if (bag == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for knapsack.\n");
        return NULL;
    }

    bag->maxWeight = maxWeight;
    bag->availableWeight = maxWeight;
    bag->itemCount = 0;
    bag->itemCapacity = itemCapacity;
    bag->items = malloc(itemCapacity * sizeof(Item *));
    if (bag->items == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for knapsack items.\n");
        free(bag);
        return NULL;
    }

    return bag;
}

// Free the memory allocated for the knapsack bag and its items.
void knapsack_free(const Knapsack *bag) {
    if (bag == NULL) {
        return;
    }

    // Free each item in the knapsack.
    for (int i = 0; i < bag->itemCount; i++) {
        free(bag->items[i]);
    }

    // Free the items array.
    free(bag->items);

    // Finally, free the knapsack structure itself.
    free((void *) bag);
}

// Add an item to the knapsack, updating available weight and item count.
// Counter for current items in knapsack also serves as index for new item.
void add_item_to_knapsack(Knapsack *bag, Item *item) {
    if (bag == NULL || item == NULL) {
        fprintf(stderr, "Error: Knapsack bag or item is NULL.\n");
        return;
    }
    if (bag->itemCount >= bag->itemCapacity) {
        fprintf(stderr, "Error: Knapsack bag is full. Consider expanding capacity.\n");
        return;
    }
    if (item->weight > bag->availableWeight) {
        fprintf(stderr, "Error: Item weight exceeds available weight in knapsack.\n");
        return;
    }

    bag->items[bag->itemCount] = item;
    bag->availableWeight -= item->weight;
    bag->itemCount++;
}

Item *get_item_from_knapsack(const Knapsack *bag, int index) {
    if (bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag is NULL.\n");
        return NULL;
    }
    if (index < 0 || index >= bag->itemCount) {
        fprintf(stderr, "Error: Index out of bounds for knapsack items.\n");
        return NULL;
    }

    return bag->items[index];
}

// Reallocate the knapsack's items' array to a new capacity, preserving existing items.
// May not be needed, but it's there in case the items array has to accommodate more items.
// May not need it, but it's there just in case.
void expand_knapsack_item_capacity(Knapsack *bag, int newCapacity) {
    if (bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag is NULL.\n");
        return;
    }

    if (newCapacity <= bag->itemCapacity) {
        fprintf(stderr, "Error: New capacity must be greater than current capacity.\n");
        return;
    }

    // Reallocate memory for the items array to the new capacity.
    Item **newItemsArray = realloc(bag->items, newCapacity * sizeof(Item *));
    if (newItemsArray == NULL) {
        fprintf(stderr, "Error: Memory reallocation failed for knapsack items.\n");
        return;
    }

    bag->items = newItemsArray;
    bag->itemCapacity = newCapacity;
}
