// demo_mode.c

#include "demo_mode.h"
#include "tex_generator.h"
#include <string.h>

const int DEMO_MAX_KNAPSACK_CAPACITY = 15;
const size_t DEMO_MAX_ITEMS = 6;
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
        "Knapsack Resolver - Demo Mode");

    // tex_problem(texFile,demoItemList, DEMO_MAX_KNAPSACK_CAPACITY);
    tex_demo_mode_def_header(texFile, demoItemList, 
        DEMO_MAX_KNAPSACK_CAPACITY, DEMO_MAX_ITEM_VALUE, DEMO_MAX_ITEM_WEIGHT);

    tex_item_list(texFile, demoItemList);

    // -- 1/0 Knapsack DP run for demo mode -- //

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

    //Writes result on .tex
    //tex_dp_table(texFile, &dpResult, demoItemList);

    //Writes run stats on .tex
    tex_dp_run_stats(texFile, dpResult, demoItemList);
    
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
    KnapsackRun simpleGreedyRun = simple_greedy_fill_knapsack(simpleGreedyKnapsack, demoItemList);
    
    if (simpleGreedyRun.bag == NULL || simpleGreedyRun.executionTime <= 0) {
        fprintf(stderr, "Error: Simple Greedy algorithm failed to produce a valid knapsack bag.\n");
        knapsack_free(simpleGreedyKnapsack);
        item_list_free(demoItemList);
        return;
    } 
    
    tex_greedy_run_stats(texFile, simpleGreedyRun, false);
    
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
    KnapsackRun proportionalGreedyRun = proportional_greedy_fill_knapsack(proportionalGreedyKnapsack, demoItemList);
    if (proportionalGreedyRun.bag == NULL || proportionalGreedyRun.executionTime <= 0) {
        fprintf(stderr, "Error: Proportional Greedy algorithm failed to produce a valid knapsack bag.\n");
        knapsack_free(proportionalGreedyKnapsack);
        item_list_free(demoItemList);
        knapsack_free(dpKnapsackRun);
        return;
    }
    tex_greedy_run_stats(texFile, proportionalGreedyRun, true);

    knapsack_free(simpleGreedyRun.bag);
    knapsack_free(proportionalGreedyRun.bag);

    // Free allocated memory for Demo mode's item list.
    item_list_free(demoItemList);

    tex_end(texFile);
    fclose(texFile);

    //Create PDF
    char command[128];
    char auxFilename[64];
    char logFilename[64];
    char openCommand[128];
    char pdfFilename[64];

    snprintf(command,sizeof(command),
        "pdflatex -interaction=nonstopmode \"%s\" > /dev/null 2>&1",texFilename);

    snprintf(auxFilename, sizeof(auxFilename), "%s", texFilename);
    snprintf(logFilename, sizeof(logFilename), "%s", texFilename);
    snprintf(pdfFilename, sizeof(pdfFilename), "%s", texFilename);
    
    //change .tex for .pdf
    pdfFilename[strlen(pdfFilename) - 3] = '\0';
    strcat(pdfFilename, "pdf");

    snprintf(openCommand, sizeof(openCommand),"evince \"%s\" &", pdfFilename);
    
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

    //Display pdf
    system(openCommand);

    // -- Completion of Demo mode run --//
    printf("Demo mode run completed.\n");
}
