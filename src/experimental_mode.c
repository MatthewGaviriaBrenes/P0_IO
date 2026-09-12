// experimental_mode.c

#include "demo_mode.h"

// Values for the start, end and steps for Knapsack weight capacity.
const int EXP_START_KNAPSACK_WEIGHT = 100;
const int EXP_END_KNAPSACK_WEIGHT = 1000;
const int EXP_STEP_KNAPSACK_WEIGHT = 100;

// Values for the start, end and step values for Item county.
const int EXP_START_ITEM_COUNT = 10;
const int EXP_END_ITEM_COUNT = 100;
const int EXP_STEP_ITEM_COUNT = 10;

// Max value for each item when generating random item lists in Experimental mode.
const int EXP_ITEM_MAX_VALUE = 100;


// Run a group of cases for the experimental mode.
// caseGroupParameter is used to track a case group.
void run_exp_case_group(int caseCount, int knapsackWeight, int itemCount) {

    // Loop for cases to run with given limits on knapsack weight and item count.
    for (int caseNum = 1; caseNum <= caseCount; caseNum++) {
        // Create items list for case
        ItemList *itemList = item_list_create_random((size_t) itemCount, EXP_ITEM_MAX_VALUE, knapsackWeight);
        
        // Abort execution if item list could not be created.
        if (itemList == NULL) {
            fprintf(stderr, "List of items could not be created. Aborting execution of program.\n");
            exit(EXIT_FAILURE);
        }   

        //TODO: Run knapsack algorithms.

        //TODO: Remove screen prints.
        printf("CASE: %d, WEIGHT: %d, ITEMCOUNT: %d\n", caseNum, knapsackWeight, itemCount);

        // Collect average metrics for all cases with the given knapsack and item constraints.

        // Free memory for case's item list.
        item_list_free(itemList);
    }

}




// Run the experimental mode.
// Uses the number argument *n) passed by the "-E=n" parameter.
// For each case group from 1 to n, run 100 cases with varying item and weight capacities.
void run_exp_mode(long caseCount) {

    if (caseCount < 1) {
        fprintf(stderr, "Number of case groups must be higher than 0.\n");
    }

    printf("Running in Experimental mode - Input value: %ld - Cases: %ld\n", 
        caseCount, (caseCount * 100));

    // Loop to iterate over all weight options for the knapsack.
    for (int knapsackWeight = EXP_START_KNAPSACK_WEIGHT; knapsackWeight <= EXP_END_KNAPSACK_WEIGHT; 
            knapsackWeight += EXP_STEP_KNAPSACK_WEIGHT) {
                
                // Loop to iterate over all item count options to fill the knapsack.
                for (int itemCount = EXP_START_ITEM_COUNT; itemCount <= EXP_END_ITEM_COUNT; 
                        itemCount += EXP_STEP_ITEM_COUNT) {
                            run_exp_case_group(caseCount, knapsackWeight, itemCount);
                }
    }
    
    //TODO: Send collected data to TEX file.

    printf("Experimental mode finished running.\n");
}