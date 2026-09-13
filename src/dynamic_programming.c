// dynamic_programming.c

#include <time.h>

#include "dynamic_programming.h"

// Small local helper
static int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// Allocate a rows x cols int matrix. Returns NULL (and prints to stderr) on
// failure, freeing anything already allocated.
static int **allocate_dp_table(int rows, int cols) {
    int **table = malloc((size_t) rows * sizeof(int *));
    if (table == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for DP table rows.\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        table[i] = malloc((size_t) cols * sizeof(int));
        if (table[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for DP table row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(table[k]);
            }
            free(table);
            return NULL;
        }
    }

    return table;
}

DPKnapsackResult dp_knapsack_solve(Knapsack *bag, const ItemList *itemsList) {
    DPKnapsackResult dpResult;
    dpResult.table = NULL;
    dpResult.rows = 0;
    dpResult.cols = 0;
    dpResult.result.executionTime = 0.0;
    dpResult.result.bag = bag;

    if (bag == NULL || itemsList == NULL) {
        fprintf(stderr, "Error: Knapsack bag or item list is NULL.\n");
        return dpResult;
    }
    if (bag->maxWeight < 0) {
        fprintf(stderr, "Error: Knapsack capacity cannot be negative.\n");
        return dpResult;
    }

    const int capacity = bag->maxWeight;
    const int n = (int) itemsList->size;
    const int rows = n + 1;
    const int cols = capacity + 1;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int **table = allocate_dp_table(rows, cols);
    if (table == NULL) {
        return dpResult; // error already reported by allocate_dp_table
    }

    // Base case: with 0 items available, the best value is 0 no matter the
    // capacity.
    for (int w = 0; w < cols; w++) {
        table[0][w] = 0;
    }

    // Bottom-up fill: table[i][w] considers whether to take item (i-1).
    for (int i = 1; i < rows; i++) {
        const Item *item = get_item_from_list(itemsList, (size_t) (i - 1));
        const int weight = (item != NULL) ? item->weight : 0;
        const int value  = (item != NULL) ? item->value  : 0;

        for (int w = 0; w < cols; w++) {
            if (weight <= w) {
                table[i][w] = max_int(table[i - 1][w],
                                       table[i - 1][w - weight] + value);
            } else {
                table[i][w] = table[i - 1][w];
            }
        }
    }

    // Backtrack through the table to recover which items were chosen and
    // add them to the knapsack bag.
    int w = capacity;
    for (int i = rows - 1; i >= 1; i--) {
        if (table[i][w] != table[i - 1][w]) {
            Item *item = get_item_from_list(itemsList, (size_t) (i - 1));
            if (item != NULL) {
                add_item_to_knapsack(bag, item);
                w -= item->weight;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    const double elapsedMs = (end.tv_sec - start.tv_sec) * 1000.0
                            + (end.tv_nsec - start.tv_nsec) / 1e6;

    dpResult.table = table;
    dpResult.rows = rows;
    dpResult.cols = cols;
    dpResult.result.executionTime = elapsedMs;
    dpResult.result.bag = bag;

    return dpResult;
}

void dp_result_free_table(DPKnapsackResult *dpResult) {
    if (dpResult == NULL || dpResult->table == NULL) {
        return;
    }
    for (int i = 0; i < dpResult->rows; i++) {
        free(dpResult->table[i]);
    }
    free(dpResult->table);
    dpResult->table = NULL;
    dpResult->rows = 0;
    dpResult->cols = 0;
}

void print_dp_table(const DPKnapsackResult *dpResult, const ItemList *itemsList) {
    if (dpResult == NULL || dpResult->table == NULL) {
        fprintf(stderr, "Error: DP table is NULL.\n");
        return;
    }

    printf("\nDynamic Programming Table (columns = items considered 0..n, rows = capacity/weight 0..W):\n\n");

    // Header row: one column per item i = 1..n.
    printf("%8s", "w \\ i");
    for (int i = 1; i < dpResult->rows; i++) {
        char label[32];
            const Item *item = (itemsList != NULL)
                                    ? get_item_from_list(itemsList, (size_t) (i -1))
                                    : NULL;
            if (item != NULL) {
                snprintf(label, sizeof(label), "i=%d(%d,%d)", i, item->value, item->weight);
            } else {
                snprintf(label, sizeof(label), "i=%d", i);
            }
 
        printf("%12s", label);
    }
    printf("\n");

    // One row per capacity value w = 0..W, going down.
    for (int w = 0; w < dpResult->cols; w++) {
        printf("%8d", w);
        for (int i = 1; i < dpResult->rows; i++) {
            printf("%12d", dpResult->table[i][w]);
        }
        printf("\n");
    }
    printf("\n");
}
