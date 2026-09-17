#ifndef TEX_GENERATOR_H
#define TEX_GENERATOR_H

#include <stdio.h>
#include <stddef.h>

#include "knapsack_items.h"
#include "dynamic_programming.h"

FILE *tex_create_file(const char *filename);
void tex_gen_filename(char *buffer, size_t bufferSize);
void tex_preamble(FILE *file, const char *title);
void tex_problem(FILE *file, const ItemList *items, int capacity);
void tex_dp_table(FILE *file, const DPKnapsackResult *dpResult, const ItemList *itemsList);
void tex_time_table(FILE *file, const char *title, const double results[10][10]);
void tex_accuracy_table(FILE *file, const char *title, const double results[10][10]);
void tex_end(FILE *file);

#endif