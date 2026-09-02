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

// Free the memory allocated for the knapsack bag.
// Items used by the knapsack are not freed here, as they can be reused for other knapsack problem runs.
// They should be freed separately if not needed anymore.
void knapsack_free(Knapsack *bag) {
    if (bag == NULL) {
        return;
    }

    // For each item in the knapsack, mark it as available again and remove the pointer from the knapsack.
    // Items themselves are not freed, as they can be reused for other knapsack problem runs.
    for (int i = 0; i < bag->itemCount; i++) {
        bag->items[i]->available = true;
        bag->items[i] = NULL; 
    }

    bag->totalValue = 0;

    // Free the pointer to the knapsack's items array.
    free(bag->items);

    // Finally, free the knapsack structure itself.
    free(bag);
}

// Add an item to the knapsack, updating available weight and item count.
// Counter for current items in knapsack also serves as index for new item.
// Returns pointer to item if it could be added.
// Return NULL if item could not be added (e.g., due to weight constraints).
Item *add_item_to_knapsack(Knapsack *bag, Item *item) {
    if (bag == NULL || item == NULL) {
        fprintf(stderr, "Error: Knapsack bag or item is NULL.\n");
        return NULL;
    }
    if (bag->itemCount >= bag->itemCapacity) {
        fprintf(stderr, "Error: Knapsack bag is full. Consider expanding capacity.\n");
        return NULL;
    }
    if (item->weight > bag->availableWeight) {
        fprintf(stderr, "Error: Item weight exceeds available weight in knapsack.\n");
        return NULL;
    }

    bag->items[bag->itemCount] = item;
    bag->availableWeight -= item->weight;
    bag->itemCount++;
    return item;
}

// Get an item from the knapsack by index.
// Returns NULL pointer if index is out of bounds (e.g. no item at that index) 
// or if the knapsack doesn't exist (NULL pointer).
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

// Check if an item is already in the knapsack to avoid adding duplicates.
//TODO: Review if need to remove (for non-binary knapsack problem, duplicates may be allowed).
bool is_item_already_in_knapsack(const Knapsack *bag, const Item *item) {
    if (bag == NULL || item == NULL) {
        fprintf(stderr, "Error: Knapsack bag or item is NULL.\n");
        return false;
    }

    for (int i = 0; i < bag->itemCount; i++) {
        if (bag->items[i] == item) {
            return true; // Item is already in the knapsack.
        }
    }
    return false; // Item is not in the knapsack.
}