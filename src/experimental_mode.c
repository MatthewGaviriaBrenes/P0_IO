// experimental_mode.c

//#include "demo_mode.h"
#include "experimental_mode.h"
#include "tex_generator.h"
#include <string.h>

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


// Run the simple greedy algorithm for a specific knapsack case in Experimental mode.
// Return NULL to indicate failure.
KnapsackRun *exp_run_sgAlgorithm(int knapsackMaxWeight, ItemList *itemList) {
    // Create a knapsack with the specified weight and item capacity.
    Knapsack *knapsack = knapsack_create(knapsackMaxWeight, itemList->size);
    if (knapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Simple Greedy algorithm.\n");
        return NULL;
    }

    return simple_greedy_fill_knapsack(knapsack, itemList);
}

// Run the proportional greedy algorithm for a specific knapsack case in Experimental mode.
// Return NULL to indicate failure.
KnapsackRun *exp_run_pgAlgorithm(int knapsackMaxWeight, ItemList *itemList) {
    // Create a knapsack with the specified weight and item capacity.
    Knapsack *knapsack = knapsack_create(knapsackMaxWeight, itemList->size);
    if (knapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Proportional Greedy algorithm.\n");
        return NULL; 
    }

    // Run the Proportional Greedy algorithm and return the result.
    KnapsackRun *result = malloc(sizeof(KnapsackRun));
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for Proportional Greedy run result.\n");
        knapsack_free(knapsack);
        return NULL; 
    }
    return proportional_greedy_fill_knapsack(knapsack, itemList);
}



// Run a group of cases for the experimental mode.
// caseGroupParameter is used to track a case group.
//TODO: Update after integrating DP executions (wait for Josue).
ExperimentResult run_exp_case_group(size_t caseCount, int knapsackMaxWeight, size_t itemCount) {
    ExperimentResult result = {0};

    //printf("\n--- Running Experimental mode for case group - Knapsack Weight: %d, Item Count: %zu ---\n", knapsackMaxWeight, itemCount);

    // Maximum weight for items to fill knapsack is 40% of the knapsack capacity.
    int itemMaxWeight = knapsackMaxWeight * 0.4; 

    // Lists to compile results of all runs for each algorithm in the case group.
    // dp (Dynamic Programming), sg (Simple Greedy), pg (Proportional Greedy)
    // KnapsackRunList *dpRuns = knapsack_run_list_create((size_t) caseCount);
    KnapsackRunList *sgRuns = knapsack_run_list_create(caseCount);
    KnapsackRunList *pgRuns = knapsack_run_list_create(caseCount);
    KnapsackRunList *dpRuns = knapsack_run_list_create(caseCount);

    // Abort execution if any of the run lists could not be created.
    //TODO: Update after integrating DP executions (wait for Josue).
    if (/*drRuns == NULL ||*/ sgRuns == NULL || pgRuns == NULL) {
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

        //printf("\n-- Running case %d of %zu for Knapsack Weight: %d, Item Count: %zu --\n", caseNum + 1, caseCount, knapsackMaxWeight, itemCount);

        // Create item list for the case.
        itemLists[caseNum] = item_list_create_random(itemCount, EXP_ITEM_MAX_VALUE, itemMaxWeight);

        //printf("\n--- Generated random item list for case %d:\n", caseNum + 1);
        print_items_list(itemLists[caseNum]);

        // --------------------------- //
        // Run the Dynamic Programming algorithm and store the run result in the proper run list.
        //reset_item_list_availability(itemLists[caseNum]);
        Knapsack *dpKnapsack = knapsack_create(knapsackMaxWeight, itemLists[caseNum]->size);

        if (dpKnapsack == NULL) {
            fprintf(stderr, "Error: Failed to create knapsack for Dynamic Programming algorithm.\n");
            exit(EXIT_FAILURE);
        }

        DPKnapsackResult dpResult = dp_knapsack_solve(dpKnapsack, itemLists[caseNum]);

        if (dpResult.result.bag == NULL) {
            fprintf(stderr, "Error: Dynamic Programming algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }

        //Add run result to Dynamic Programming run list
        //Abort execution if the entry could not be added
        if (knapsack_run_list_add_entry(dpRuns, dpResult.result) == NULL) {
            fprintf(stderr, "Error: Failed to add Dynamic Programming run result to the run list for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        //print_knapsack_run(&dpResult.result);
        reset_item_list_availability(itemLists[caseNum]);
        // --------------------------- //


        // Run the Simple Greedy algorithm and store the run result in the proper run list.
        KnapsackRun *sgRun = exp_run_sgAlgorithm(knapsackMaxWeight, itemLists[caseNum]);
        if (sgRun == NULL) {
            fprintf(stderr, "Error: Simple Greedy algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        }
        // Add the run result to the Simple Greedy run list. 
        // Abort execution if the entry could not be added.
        if (knapsack_run_list_add_entry(sgRuns, *sgRun) == NULL) {
            fprintf(stderr, "Error: Failed to add Simple Greedy run result to the run list for case %d.\n", caseNum + 1);
            exit(EXIT_FAILURE);
        } 
        //print_knapsack_run(sgRun);
        reset_item_list_availability(itemLists[caseNum]);

        // Run the Proportional Greedy algorithm and store the run result in the proper run list.
        KnapsackRun *pgRun = exp_run_pgAlgorithm(knapsackMaxWeight, itemLists[caseNum]);
        if (pgRun == NULL) {
            fprintf(stderr, "Error: Proportional Greedy algorithm failed to produce a valid knapsack run for case %d.\n", caseNum + 1);
            knapsack_run_list_free(sgRuns);
            exit(EXIT_FAILURE);
        }
        // Add the run result to the Proportional Greedy run list. 
        // Abort execution if the entry could not be added.
        if (knapsack_run_list_add_entry(pgRuns, *pgRun) == NULL) {
            fprintf(stderr, "Error: Failed to add Proportional Greedy run result to the run list for case %d.\n", caseNum + 1);

            knapsack_run_list_free(sgRuns);
            knapsack_run_list_free(pgRuns);
            exit(EXIT_FAILURE);
        }
        //print_knapsack_run(pgRun);
        reset_item_list_availability(itemLists[caseNum]);
    }

    // --- Getting average execution times for SG, PG and DP algorithms --- 
    // Get average execution times for all three algorithms in the case group.
    //TODO: Update after integrating DP executions (wait for Josue).
    double avgSimpleGreedyTime = get_knapsack_run_avg_execution_time(sgRuns);
    double avgProportionalGreedyTime = get_knapsack_run_avg_execution_time(pgRuns);
    double avgDynamicProgrammingTime = get_knapsack_run_avg_execution_time(dpRuns);

    result.dynamicProgrammingTime = avgDynamicProgrammingTime;
    result.simpleGreedyTime = avgSimpleGreedyTime;
    result.proportionalGreedyTime = avgProportionalGreedyTime;

    result.simpleGreedyAccuracy = get_knapsack_runs_match_ratio(dpRuns, sgRuns);
    result.proportionalGreedyAccuracy = get_knapsack_runs_match_ratio(dpRuns, pgRuns);
    

    //double avgDynamicProgrammingTime = get_knapsack_run_avg_execution_time(dynamicProgrammingRuns);
    //TODO: Send to TEX file.

    // --- Getting match ratios (SG/PG vs DP) --- 
    //TODO: Send average execution times to TEX file.
    //TODO: Update after integrating DP executions (wait for Josue).
    //double sg_dp_match_ratio = get_knapsack_runs_match_ratio(dpRuns, sgRuns);
    //double pg_dp_match_ratio = get_knapsack_runs_match_ratio(dpRuns, pgRuns);
    //TODO: Send to TEX file.

    // --- Memory Cleanup ---
    // Clean run results first
    knapsack_run_list_free(sgRuns);
    knapsack_run_list_free(pgRuns);
    knapsack_run_list_free(dpRuns);

    // Clean item lists
    for (int caseNum = 0; caseNum < caseCount; caseNum++) {
        item_list_free(itemLists[caseNum]);
    }
    free(itemLists);
    return result;
}

// Run the experimental mode.
// Uses the number argument *n) passed by the "-E=n" parameter.
// For each case group from 1 to n, run 100 cases with varying item and weight capacities.
void run_exp_mode(size_t caseCount) {

    ExperimentResult result;
    int capacityIndex, itemIndex;

    double dpTimes[10][10] = {0}, sgTimes[10][10] = {0},
           pgTimes[10][10] = {0}, sgAccuracy[10][10] = {0},
           pgAccuracy[10][10] = {0};

    //printf("Running in Experimental mode - Input value: %zu - Cases: %zu\n", caseCount, (caseCount * 100));

    // Loop to iterate over all weight options for the knapsack.
    for (int knapsackMaxWeight = EXP_START_KNAPSACK_WEIGHT_CAPACITY
        ; knapsackMaxWeight <= EXP_END_KNAPSACK_WEIGHT_CAPACITY
        ; knapsackMaxWeight += EXP_STEP_KNAPSACK_WEIGHT_CAPACITY) {
            // Loop to iterate over all item count options to fill the knapsack.
            for (size_t itemCount = EXP_START_ITEM_COUNT; itemCount <= EXP_END_ITEM_COUNT; 
                    itemCount += EXP_STEP_ITEM_COUNT) {
                    
                    result = run_exp_case_group(caseCount, knapsackMaxWeight, itemCount);
                    capacityIndex = (knapsackMaxWeight - EXP_START_KNAPSACK_WEIGHT_CAPACITY)/EXP_STEP_KNAPSACK_WEIGHT_CAPACITY;
                    itemIndex = (itemCount - EXP_START_ITEM_COUNT)/EXP_STEP_ITEM_COUNT;

                    //printf("capacity=%d, items=%zu, indexes=[%d][%d]\n",knapsackMaxWeight,itemCount,capacityIndex,itemIndex);
                    dpTimes[capacityIndex][itemIndex] = result.dynamicProgrammingTime;
                    sgTimes[capacityIndex][itemIndex] = result.simpleGreedyTime;
                    pgTimes[capacityIndex][itemIndex] = result.proportionalGreedyTime;
                    sgAccuracy[capacityIndex][itemIndex] = result.simpleGreedyAccuracy;
                    pgAccuracy[capacityIndex][itemIndex] = result.proportionalGreedyAccuracy;

            }
    }
    
    //TODO: Send collected data to TEX file.

    //Create .tex
    char texFilename[64];
    tex_gen_filename(texFilename, sizeof(texFilename));
    FILE *texFile = tex_create_file(texFilename);

    if (texFile == NULL) {
        fprintf(stderr, "Error: Failed to create TEX file.\n");
        return;
    }
    tex_preamble(texFile, 
        "0/1 Knapsack Problem - Experimental Mode");
    tex_time_table(texFile, 
        "Dynamic Programming Average Execution Time", dpTimes);
    tex_time_table(texFile, 
        "Simple Greedy Average Execution Time", sgTimes);
    tex_time_table(texFile,
        "Proportional Greedy Average Execution Time", pgTimes);
    tex_accuracy_table(texFile,
        "Simple Greedy Accuracy Compared with Dynamic Programming", sgAccuracy);
    tex_accuracy_table(texFile,
        "Proportional Greedy Accuracy Compared with Dynamic Programming", pgAccuracy);

    tex_end(texFile);
    fclose(texFile);

    //Create PDF
    char command[128];
    char auxFilename[128];
    char logFilename[128];

    snprintf(command,sizeof(command),
        "pdflatex -interaction=nonstopmode \"%s\" > /dev/null 2>&1",texFilename);

    snprintf(auxFilename, sizeof(auxFilename), "%s", texFilename);
    snprintf(logFilename, sizeof(logFilename), "%s", texFilename);

    int status = system(command);

    if (status != 0) {
        fprintf(stderr, "Error: Failed to generate PDF from TEX file.\n");
        return;
    }
    auxFilename[strlen(auxFilename) - 3] = '\0';
    logFilename[strlen(logFilename) - 3] = '\0';

    strcat(auxFilename, "aux");
    strcat(logFilename, "log");

    remove(auxFilename);
    remove(logFilename);

    printf("Experimental mode finished running.\n");
}