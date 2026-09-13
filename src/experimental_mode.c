// experimental_mode.c

#include "demo_mode.h"

// Values for the start, end and steps for Knapsack weight capacity.
const int EXP_START_KNAPSACK_WEIGHT_CAPACITY = 100;
const int EXP_END_KNAPSACK_WEIGHT_CAPACITY = 1000;
const int EXP_STEP_KNAPSACK_WEIGHT_CAPACITY = 100;

// Values for the start, end and step values for Item county.
const size_t EXP_START_ITEM_COUNT = 10;
const size_t EXP_END_ITEM_COUNT = 100;
const size_t EXP_STEP_ITEM_COUNT = 10;

// Max value for each item when generating random item lists in Experimental mode.
const int EXP_ITEM_MAX_VALUE = 100;

// Run the dynamic programming algorithm for a specific knapsack case in Experimental mode.
// Return empty result to indicate failure.
// Returned DPKnapsackResult structure contains both the DP resolution table 
// and the KnapsackRun result (execution time + filled bag).
DPKnapsackResult exp_run_dpAlgorithm(int knapsackMaxWeight, ItemList *itemList) {
    // Create a knapsack with the specified weight and item capacity.
    Knapsack *knapsack = knapsack_create(knapsackMaxWeight, itemList->size);
    if (knapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Dynamic Programming algorithm.\n");
        DPKnapsackResult emptyResult = {0};
        return emptyResult;
    }
    return dp_knapsack_solve(knapsack, itemList);
}

// Run the simple greedy algorithm for a specific knapsack case in Experimental mode.
// Returns a zero-initialized result to indicate failure.
KnapsackRun exp_run_sgAlgorithm(int knapsackMaxWeight, ItemList *itemList) {
    // Create a knapsack with the specified weight and item capacity.
    Knapsack *knapsack = knapsack_create(knapsackMaxWeight, itemList->size);
    
    if (knapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Simple Greedy algorithm.\n");
        return (KnapsackRun){0};
    }

    return simple_greedy_fill_knapsack(knapsack, itemList);
}

// Run the proportional greedy algorithm for a specific knapsack case in Experimental mode.
// Returns a zero-initialized result to indicate failure.
KnapsackRun exp_run_pgAlgorithm(int knapsackMaxWeight, ItemList *itemList) {
    // Create a knapsack with the specified weight and item capacity.
    Knapsack *knapsack = knapsack_create(knapsackMaxWeight, itemList->size);
    
    if (knapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Simple Greedy algorithm.\n");
        return (KnapsackRun){0};
    }

    return proportional_greedy_fill_knapsack(knapsack, itemList);
}

// Run a group of cases for the experimental mode.
// caseGroupParameter is used to track a case group.
//TODO: Update after integrating DP executions (wait for Josue).
void run_exp_case_group(size_t caseCount, int knapsackMaxWeight, size_t itemCount) {

    printf("\n--- Running Experimental mode for case group - Knapsack Weight: %d, Item Count: %zu ---\n", knapsackMaxWeight, itemCount);

    // Maximum weight for items to fill knapsack is 40% of the knapsack capacity.
    int itemMaxWeight = knapsackMaxWeight * 0.4; 

    // Lists to compile results of all runs for each algorithm in the case group.
    // dp (Dynamic Programming), sg (Simple Greedy), pg (Proportional Greedy)
    
    // DP algoritm results require two lists (one for the DP table and one for the knapsack run result).
    DPKnapsackResult *dpResults = malloc(sizeof(DPKnapsackResult) * (size_t) caseCount);
    KnapsackRunList *dpRuns = knapsack_run_list_create(caseCount);
    KnapsackRunList *sgRuns = knapsack_run_list_create(caseCount);
    KnapsackRunList *pgRuns = knapsack_run_list_create(caseCount);

    // Abort execution if any of the run lists could not be created.
    //TODO: Update after integrating DP executions (wait for Josue).
    if (dpRuns == NULL || sgRuns == NULL || pgRuns == NULL) {
        fprintf(stderr, "Error: Could not create run lists for experimental mode. Aborting execution of program.\n");
        exit(EXIT_FAILURE);
    }

    // Create an array of item lists to store the random items generated for each case.
    ItemList **itemLists = malloc(sizeof(ItemList *) * (size_t) caseCount);
    if (itemLists == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for item lists in experimental mode.\n");
        exit(EXIT_FAILURE);
    }
    
    // Loop for case run number.
    for (int caseNum = 0; caseNum < caseCount; caseNum++) {
        printf("\n-- Running case %d of %zu for Knapsack Weight: %d, Item Count: %zu --\n", caseNum + 1, caseCount, knapsackMaxWeight, itemCount);

        // Create item list for the case.
        itemLists[caseNum] = item_list_create_random(itemCount, EXP_ITEM_MAX_VALUE, itemMaxWeight);

        printf("\n--- Generated random item list for case %d:\n", caseNum + 1);
        print_items_list(itemLists[caseNum]);

        // --------------------------- //
        // Run the Dynamic Programming algorithm and store the run result in the proper run list.
        //TODO: Add after implementing the dynamic programming algorithm.
        //reset_item_list_availability(itemLists[caseNum]);
        // --------------------------- //
        dpResults[caseNum] = exp_run_dpAlgorithm(knapsackMaxWeight, itemLists[caseNum]);
        if (dpResults[caseNum].table == NULL || dpResults[caseNum].result.bag == NULL) {
            fprintf(stderr, "Error: Dynamic Programming algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        if (!knapsack_run_list_add_entry(dpRuns, dpResults[caseNum].result)) {
            fprintf(stderr, "Error: Failed to add Dynamic Programming run result to the run list for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        print_dp_table(&dpResults[caseNum], itemLists[caseNum]);
        print_knapsack_run(dpResults[caseNum].result);
        reset_item_list_availability(itemLists[caseNum]);

        // Run the Simple Greedy algorithm and store the run result in the proper run list.
        KnapsackRun sgRun = exp_run_sgAlgorithm(knapsackMaxWeight, itemLists[caseNum]);
        if (sgRun.bag == NULL || sgRun.executionTime <= 0) {
            fprintf(stderr, "Error: Simple Greedy algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }

        if (!knapsack_run_list_add_entry(sgRuns, sgRun)) {
            fprintf(stderr, "Error: Failed to add Simple Greedy run result to the run list for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        
        print_knapsack_run(sgRun);
        reset_item_list_availability(itemLists[caseNum]);

        // Run the Proportional Greedy algorithm and store the run result in the proper run list.

        KnapsackRun pgRun = exp_run_pgAlgorithm(knapsackMaxWeight, itemLists[caseNum]);
        if (pgRun.bag == NULL || pgRun.executionTime <= 0) {
            fprintf(stderr, "Error: Proportional Greedy algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        if (!knapsack_run_list_add_entry(pgRuns, pgRun)) {
            fprintf(stderr, "Error: Failed to add Proportional Greedy run result to the run list for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        print_knapsack_run(pgRun);
        reset_item_list_availability(itemLists[caseNum]);
    }

    // --- Getting average execution times for SG, PG and DP algorithms --- 
    // Get average execution times for all three algorithms in the case group.
    //TODO: Update after integrating DP executions (wait for Josue).
    double avgSimpleGreedyTime = get_knapsack_run_avg_execution_time(sgRuns);
    double avgProportionalGreedyTime = get_knapsack_run_avg_execution_time(pgRuns);

    printf("\n-- Algorithm Average Execution Times for Knapsack (Weight Capacity: %d, Item Count: %zu) --\n", knapsackMaxWeight, itemCount);
    printf("> Simple Greedy: %.5f ms\n", avgSimpleGreedyTime);
    printf("> Proportional Greedy: %.5f ms\n", avgProportionalGreedyTime);

    //double avgDynamicProgrammingTime = get_knapsack_run_avg_execution_time(dynamicProgrammingRuns);
    //TODO: Send to TEX file.

    // --- Getting match ratios (SG/PG vs DP) --- 
    //TODO: Send average execution times to TEX file.
    //TODO: Update after integrating DP executions (wait for Josue).
    // The match ratio is the percentage of times the Greedy algorithms produced the same total value as the Dynamic Programming algorithm for the same case.
    double dp_sg_match_ration = get_knapsack_runs_match_ratio(dpRuns, sgRuns);
    double dp_pg_match_ratio = get_knapsack_runs_match_ratio(dpRuns, pgRuns);
    printf("\n-- Algorithm Match Ratios for Knapsack (Weight Capacity: %d, Item Count: %zu) --\n", knapsackMaxWeight, itemCount);
    printf("> Simple Greedy vs Dynamic Programming: %.2f%%\n", dp_sg_match_ration * 100.0);
    printf("> Proportional Greedy vs Dynamic Programming: %.2f%%\n", dp_pg_match_ratio * 100.0);

    //TODO: Send to TEX file.

    // --- Memory Cleanup ---
    // Clean run results first
    knapsack_run_list_free(sgRuns);
    knapsack_run_list_free(pgRuns);
    knapsack_run_list_free(dpRuns);

    // Clear DP tables for each case in the case group.
    for (size_t caseNum = 0; caseNum < caseCount; caseNum++) {
        dp_result_free_table(&dpResults[caseNum]);
    }

    // Clean item lists
    for (size_t caseNum = 0; caseNum < caseCount; caseNum++) {
        item_list_free(itemLists[caseNum]);
    }

    //DEBUG: Wait for user input before continuing to the next case group.
    printf("\nPress Enter to continue to the next case group...");
    getchar();
}

// Run the experimental mode.
// Uses the number argument *n) passed by the "-E=n" parameter.
// For each case group from 1 to n, run 100 cases with varying item and weight capacities.
void run_exp_mode(size_t caseCount) {
    printf("Running in Experimental mode - Input value: %zu - Cases: %zu\n", caseCount, (caseCount * 100));

    // Loop to iterate over all weight options for the knapsack.
    for (int knapsackMaxWeight = EXP_START_KNAPSACK_WEIGHT_CAPACITY
        ; knapsackMaxWeight <= EXP_END_KNAPSACK_WEIGHT_CAPACITY
        ; knapsackMaxWeight += EXP_STEP_KNAPSACK_WEIGHT_CAPACITY) {
            // Loop to iterate over all item count options to fill the knapsack.
            for (size_t itemCount = EXP_START_ITEM_COUNT; itemCount <= EXP_END_ITEM_COUNT; 
                    itemCount += EXP_STEP_ITEM_COUNT) {
                        run_exp_case_group(caseCount, knapsackMaxWeight, itemCount);
            }
    }
    
    //TODO: Send collected data to TEX file.

    printf("Experimental mode finished running.\n");
}