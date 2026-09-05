// demo_mode.c

#include "demo_mode.h"

const int DEMO_MAX_KNAPSACK_CAPACITY = 15;
const int DEMO_MAX_ITEMS = 6;
const int DEMO_MAX_ITEM_VALUE = 20;
const int DEMO_MAX_ITEM_WEIGHT = 7;

void run_demo_mode() {
    printf("Running in Demo mode.\n");
    // Create a random set of knapsack items for demo mode.
    printf("\n--- Generating list of random items for run...\n");
    ItemList *demoItemList = item_list_create_random(DEMO_MAX_ITEMS, DEMO_MAX_ITEM_VALUE, DEMO_MAX_ITEM_WEIGHT);

    // Abort execution if item list creation failed.
    if (demoItemList == NULL) {
        fprintf(stderr, "Error: Failed to create demo item list.\n");
        return;
    } else {
        print_items_list(demoItemList);
    }

    // -- 1/0 Knapsack DP run for demo mode -- //
    // TODO: To be added after implementing the resepctive algorithm.

    Knapsack *dpKnapsackRun = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);
    // Abort execution if knapsack creation failed for DP run.
    if (dpKnapsackRun == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for 1/0 DP run.\n");
        item_list_free(demoItemList);
        return;
    } 
    //TODO: Implement 1/0 Knapsack DP algorithm and measure execution time.

    // -- Simple Greedy run for demo mode -- //
    printf("\n--- Running Simple Greedy algorithm for Ddemo mode.\n");
    Knapsack *simpleGreedyKnapsack = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);
   
    // Abort execution if knapsack creation failed for Simple Greedy run.
    if (simpleGreedyKnapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Simple Greedy run.\n");
        item_list_free(demoItemList);
        return;
    } 
    
    // Store results in a KnapsackRunResult structure, then print results on screen for now.
    //TODO: Replace on-screen print with output to TEX file.
    KnapsackRunResult simpleGreedyRun = simple_greedy_fill_knapsack(simpleGreedyKnapsack, demoItemList);
    print_knapsack_run_result(&simpleGreedyRun);

    // Reset item availability for the next algorithm run.
    reset_item_list_availability(demoItemList); 

    // -- Proportional Greedy run for demo mode. -- //
    printf("\n--- Running Proportional Greedy algorithm for Ddemo mode.\n");
    Knapsack *proportionalGreedyKnapsack = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);

    // Abort execution if knapsack creation failed for Proportional Greedy run.
    if (proportionalGreedyKnapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Proportional Greedy run.\n");
        knapsack_free(simpleGreedyKnapsack);
        item_list_free(demoItemList);
        return;
    }

    // Store results in a KnapsackRunResult structure, then print results on screen for now.
    //TODO: Replace on-screen print with output to TEX file.
    KnapsackRunResult proportionalGreedyRun = proportional_greedy_fill_knapsack(proportionalGreedyKnapsack, demoItemList);
    print_knapsack_run_result(&proportionalGreedyRun);
    
    // -- Completion of Demo mode run --//
    printf("Demo mode run completed.\n");

    // Free allocated memory for knapsacks and item list.
    knapsack_free(simpleGreedyKnapsack);
    knapsack_free(proportionalGreedyKnapsack);
    item_list_free(demoItemList);
}