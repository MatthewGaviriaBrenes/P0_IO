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

void tex_dp_table(FILE *file,
    const DPKnapsackResult *dpResult,
    const ItemList *itemsList)
{
    fprintf(file, "\\section{Dynamic Programming Table}\n");
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