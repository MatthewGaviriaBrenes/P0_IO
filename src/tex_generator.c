#include <stdio.h>
#include <stdlib.h>

#include "tex_generator.h"
#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "dynamic_programming.h"
#include "knapsack_run.h"

//Creates and opens the file to write
FILE *tex_create_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create TEX file.\n");
        return NULL;
    }
    return file;
}

//Generates filename based on current date for TEX report
void tex_gen_filename(char *buffer, size_t bufferSize)
{
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(buffer, bufferSize, "%Y%m%d_%H%M%S.tex", localTime);
}

void tex_preamble(FILE *file, const char *title)
{
    fprintf(file, "\\documentclass{article}\n");
    fprintf(file, "\\usepackage{amsmath}\n");
    fprintf(file, "\\usepackage[table]{xcolor}\n");
    fprintf(file, "\\usepackage{array}\n");
    fprintf(file, "\\usepackage{booktabs}\n");
    fprintf(file, "\\usepackage[margin=1in]{geometry}\n\n");
    fprintf(file, "\\title{%s}\n", title);
    fprintf(file, "\\date{\\today}\n\n");
    fprintf(file, "\\begin{document}\n");
    fprintf(file, "\\maketitle\n\n");
}

void tex_problem(FILE *file, const ItemList *items, int capacity)
{
    fprintf(file, "\\section{Problem Definition}\n");
    fprintf(file, "Knapsack capacity: %d\n\n", capacity);
    fprintf(file, "Number of items: %zu\n\n", items->size);
    fprintf(file, "\\begin{center}\n");
    fprintf(file, "\\begin{tabular}{ccc}\n");
    fprintf(file, "\\toprule\n");
    fprintf(file, "Item & Weight & Value \\\\\n");
    fprintf(file, "\\midrule\n");

    for (size_t i = 0; i < items->size; i++) {
        fprintf(
            file,
            "%d & %d & %d \\\\\n",
            items->items[i].id,
            items->items[i].weight,
            items->items[i].value
        );
    }
    fprintf(file, "\\bottomrule\n");
    fprintf(file, "\\end{tabular}\n");
    fprintf(file, "\\end{center}\n\n");
}

void tex_exp_mode_def_header(FILE *file, size_t caseCount) {
    fprintf(file, "\\section{Problem Definition}\n");
    fprintf(file, "Number of cases per configuration: %zu\n\n", caseCount);
    fprintf(file, "Total runs for all configurations: %zu\n\n", (caseCount * 100));
}

void tex_exp_mode_stats_header(FILE *file) {
    fprintf(file, "\\section{Experimental Mode Statistics}\n");
    fprintf(file, "This section presents the aggregated results of multiple runs of the Knapsack algorithms with different configurations.\n\n");
}

void tex_dp_table(FILE *file,
    const DPKnapsackResult *dpResult,
    const ItemList *itemsList)
{
    fprintf(file, "\\subsection{Dynamic Programming Table}\n");
    fprintf(file, "\\begin{center}\n");
    fprintf(file, "\\begin{tabular}{c");

    for (int col = 0; col < dpResult->cols; col++) {
        fprintf(file, "c");
    }
    fprintf(file, "}\n");
    fprintf(file, "\\toprule\n");
    fprintf(file, "Item / Capacity");

    for (int col = 0; col < dpResult->cols; col++) {
        fprintf(file, " & %d", col);
    }
    fprintf(file, " \\\\\n");
    fprintf(file, "\\midrule\n");

    for (int row = 0; row < dpResult->rows; row++) {
        fprintf(file, "%d", row);

        for (int col = 0; col < dpResult->cols; col++) {
            if (row == 0){
                fprintf(file, " & \\cellcolor{red!25}%d", dpResult->table[row][col]);
                continue;
            }

            Item item = itemsList->items[row - 1];

            int value = dpResult->table[row][col];

            if (item.weight > col) {
                fprintf(file," & \\cellcolor{red!25}%d",value);

            } else {
                int withoutItem = dpResult->table[row - 1][col];

                int withItem = item.value +
                    dpResult->table[row - 1][col - item.weight];

                if (withItem > withoutItem) {
                    fprintf(file," & \\cellcolor{green!25}%d",value);
                } else {
                    fprintf(file," & \\cellcolor{red!25}%d",value);
                }
            }
        }
        fprintf(file, " \\\\\n");
    }
    fprintf(file, "\\bottomrule\n");
    fprintf(file, "\\end{tabular}\n");
    fprintf(file, "\\end{center}\n\n");
}

void tex_run_time(FILE *file, KnapsackRun run, const char *algorithmName) {
    fprintf(file, "Execution Time: %.6f ms\n\n", run.executionTime);
}

void tex_run_contents(FILE *file, KnapsackRun run, const char *algorithmName) {
    if (run.bag == NULL) {
        fprintf(stderr, "Error: Knapsack bag is NULL for %s algorithm.\n", algorithmName);
        return;
    }
    fprintf(file, "Total Value of Items in Knapsack: %d\n\n", run.bag->totalValue);
    fprintf(file, "Total Weight of Items in Knapsack: %d\n\n", run.bag->maxWeight - run.bag->freeWeight);
    fprintf(file, "Items in Knapsack:\n\n");
    fprintf(file, "\\begin{center}\n");
    fprintf(file, "\\begin{tabular}{ccc}\n");
    fprintf(file, "\\toprule\n");
    fprintf(file, "Item & Weight & Value \\\\\n");
    fprintf(file, "\\midrule\n");
    for (int i = 0; i < run.bag->itemCount; i++) {
        Item *item = get_item_from_knapsack(run.bag, i);
        if (item != NULL) {
            fprintf(
                file,
                "%d & %d & %d \\\\\n",
                item->id,
                item->weight,
                item->value
            );
        }
    }
    fprintf(file, "\\bottomrule\n");
    fprintf(file, "\\end{tabular}\n");
    fprintf(file, "\\end{center}\n\n");
}

void tex_dp_run_stats(FILE *file, DPKnapsackResult run, ItemList *itemsList) {
    if (run.result.executionTime == 0 || run.result.bag == NULL) {
        fprintf(stderr, "Error: Dynamic Programming run result is NULL.\n");
        return;
    }
    fprintf(file, "\\section{Dynamic Programming Algorithm Run Stats}\n");
    tex_dp_table(file, &run, itemsList);
    tex_run_time(file, run.result, "Dynamic Programming");
    tex_run_contents(file, run.result, "Dynamic Programming");
}

void tex_greedy_run_stats(FILE *file, KnapsackRun run, bool proportional) {
    const char *algorithmName = proportional ? "Proportional Greedy" : "Simple Greedy";
    fprintf(file, "\\subsection{%s Algorithm Run Stats}\n", algorithmName);
    tex_run_time(file, run, algorithmName);
    tex_run_contents(file, run, algorithmName);
}

void tex_time_table(FILE *file,const char *title,
    const double results[10][10])
{
    fprintf(file, "\\subsection{%s}\n", title);
    fprintf(file, "\\begin{center}\n");
    fprintf(file, "\\begin{tabular}{c");

    for (int col = 0; col < 10; col++) {
        fprintf(file, "c");
    }
    fprintf(file, "}\n");
    fprintf(file, "\\toprule\n");
    fprintf(file, "Capacity");

    for (int col = 0; col < 10; col++) {
        fprintf(file, " & %d", (col + 1) * 10);
    }
    fprintf(file, " \\\\\n");
    fprintf(file, "\\midrule\n");

    for (int row = 0; row < 10; row++) {

        fprintf(file, "%d", (row + 1) * 100);

        for (int col = 0; col < 10; col++) {
            fprintf(
                file,
                " & %.5f",
                results[row][col]
            );
        }

        fprintf(file, " \\\\\n");
    }
    fprintf(file, "\\bottomrule\n");
    fprintf(file, "\\end{tabular}\n");
    fprintf(file, "\\end{center}\n\n");
}

void tex_accuracy_table(FILE *file, const char *title,
    const double results[10][10])
{
    fprintf(file, "\\subsection{%s}\n", title);
    fprintf(file, "\\begin{center}\n");
    fprintf(file, "\\begin{tabular}{c");

    for (int col = 0; col < 10; col++) {
        fprintf(file, "c");
    }
    fprintf(file, "}\n");
    fprintf(file, "\\toprule\n");
    fprintf(file, "Capacity");

    for (int col = 0; col < 10; col++) {
        fprintf(file, " & %d", (col + 1) * 10);
    }
    fprintf(file, " \\\\\n");
    fprintf(file, "\\midrule\n");

    for (int row = 0; row < 10; row++) {

        fprintf(file, "%d", (row + 1) * 100);

        for (int col = 0; col < 10; col++) {
            fprintf( file, " & %.2f\\%%",
                results[row][col]*100);
        }
        fprintf(file, " \\\\\n");
    }
    fprintf(file, "\\bottomrule\n");
    fprintf(file, "\\end{tabular}\n");
    fprintf(file, "\\end{center}\n\n");
}

// Writes the end of the LaTeX document.
void tex_end(FILE *file)
{
    fprintf(file, "\\end{document}\n");
}