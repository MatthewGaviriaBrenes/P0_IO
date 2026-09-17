// demo_mode.c

#include "demo_mode.h"
#include "tex_generator.h"
#include <string.h>

const int DEMO_MAX_KNAPSACK_CAPACITY = 15;
const int DEMO_MAX_ITEMS = 6;
const int DEMO_MAX_ITEM_VALUE = 20;
const int DEMO_MAX_ITEM_WEIGHT = 7;

void run_demo_mode() {
    //printf("Running in Demo mode.\n");
    // Create a random set of knapsack items for demo mode.
    //printf("\n--- Generating list of random items for run...\n");

    ItemList *demoItemList = item_list_create_random(DEMO_MAX_ITEMS, DEMO_MAX_ITEM_VALUE, DEMO_MAX_ITEM_WEIGHT);

    // Abort execution if item list creation failed.

    if (demoItemList == NULL) {
        fprintf(stderr, "Error: Failed to create demo item list.\n");
        return;
    } /*else {
        print_items_list(demoItemList);
    }*/

    //Create .tex
    char texFilename[64];

    tex_gen_filename(texFilename, sizeof(texFilename));

    FILE *texFile = tex_create_file(texFilename);

    if (texFile == NULL) {
        item_list_free(demoItemList);
        return;
    }

    tex_preamble(texFile, 
        "0/1 Knapsack Problem - Demo Mode");

    tex_problem(texFile,demoItemList,
        DEMO_MAX_KNAPSACK_CAPACITY);

    // -- 1/0 Knapsack DP run for demo mode -- //
    // TODO: To be added after implementing the resepctive algorithm.

    Knapsack *dpKnapsackRun = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);
    // Abort execution if knapsack creation failed for DP run.
    if (dpKnapsackRun == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for 1/0 DP run.\n");
        item_list_free(demoItemList);
        knapsack_free(dpKnapsackRun);
        return;
    } 
    //printf("\n--- Running Knapsack Dynamic Programming algorithm for Demo mode.\n");
    DPKnapsackResult dpResult = dp_knapsack_solve(dpKnapsackRun, demoItemList);
    
    //print_dp_table(&dpResult, demoItemList);
    //print_knapsack_run(&dpResult.result);

    //Writes result on .tex
    tex_dp_table(texFile, &dpResult, demoItemList);
    
    dp_result_free_table(&dpResult);
    knapsack_free(dpKnapsackRun);
  
    // Reset item availability for the next algorithm run.
    reset_item_list_availability(demoItemList); 

    // -- Simple Greedy run for demo mode -- //
   // printf("\n--- Running Simple Greedy algorithm for Demo mode.\n");
    Knapsack *simpleGreedyKnapsack = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);
   
    // Abort execution if knapsack creation failed for Simple Greedy run.
    if (simpleGreedyKnapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Simple Greedy run.\n");
        item_list_free(demoItemList);
        knapsack_free(dpKnapsackRun);
        return;
    } 
    
    // Store results in a KnapsackRun structure, then print results on screen for now.
    //TODO: Replace on-screen print with output to TEX file.
    KnapsackRun *simpleGreedyRun = simple_greedy_fill_knapsack(simpleGreedyKnapsack, demoItemList);
    
    if (simpleGreedyRun == NULL || simpleGreedyRun->bag == NULL) {
        fprintf(stderr, "Error: Simple Greedy algorithm failed to produce a valid knapsack bag.\n");
        knapsack_free(simpleGreedyKnapsack);
        item_list_free(demoItemList);
        return;
    } 
    
    //print_knapsack_run(simpleGreedyRun);
    
    // Free the memory allocated for the Simple Greedy run result once it is no longer needed.
    knapsack_run_free(simpleGreedyRun);
    
    // Reset item availability for the next algorithm run.
    reset_item_list_availability(demoItemList); 

    // -- Proportional Greedy run for demo mode. -- //
    //printf("\n--- Running Proportional Greedy algorithm for Demo mode.\n");
    Knapsack *proportionalGreedyKnapsack = knapsack_create(DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEMS);

    // Abort execution if knapsack creation failed for Proportional Greedy run.
    if (proportionalGreedyKnapsack == NULL) {
        fprintf(stderr, "Error: Failed to create knapsack for Proportional Greedy run.\n");
        knapsack_free(simpleGreedyKnapsack);
        item_list_free(demoItemList);
        knapsack_free(dpKnapsackRun);
        return;
    }

    // Store results in a KnapsackRun structure, then print results on screen for now.
    //TODO: Replace on-screen print with output to TEX file.
    KnapsackRun *proportionalGreedyRun = proportional_greedy_fill_knapsack(proportionalGreedyKnapsack, demoItemList);
    if (proportionalGreedyRun == NULL || proportionalGreedyRun->bag == NULL) {
        fprintf(stderr, "Error: Proportional Greedy algorithm failed to produce a valid knapsack bag.\n");
        knapsack_free(proportionalGreedyKnapsack);
        item_list_free(demoItemList);
        return;
    }
    //print_knapsack_run(proportionalGreedyRun);

    // Free the memory allocated for the Proportional Greedy run result once it is no longer needed.
    knapsack_run_free(proportionalGreedyRun); 

    // Free allocated memory for Demo mode's item list.
    item_list_free(demoItemList);

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

    // -- Completion of Demo mode run --//
    printf("Demo mode run completed.\n");
}
