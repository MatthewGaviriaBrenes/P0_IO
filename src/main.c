// Main.c
// Entry point for program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "knapsack_items.h"
#include "knapsack_bag.h"
#include "knapsack_run.h"
#include "dynamic_programming.h"
#include "greedy_algorithms.h"
#include "demo_mode.h"
#include "experimental_mode.h"

int main(int argc, char *argv[]) 
{
    // Show info on how to use the program if not running with a single parameter. 
    if (argc != 2) 
    {
        printf("Usage: %s -X | -E=n\n", argv[0]);
        printf("-X : Demo Mode - Run a single random Knapsack case with all algorithms.\n");
        printf("-E=n : Experimental mode (100 * n cases).\n");
        return 0;
    }
    // Parse input parameter to start Demo mode (-X) or experimental mode (-E=n | n: number).
    if (strcmp(argv[1], "-X") == 0) 
    {
        run_demo_mode();
        return 0;
    } else if (strncmp(argv[1], "-E=", 3) == 0)
    {
        size_t value;
        char *end;
        errno = 0;

        value = (size_t)strtoul(argv[1] + 3, &end, 10);

        if (errno != 0 || end == argv[1] + 3 || *end != '\0') {
            printf("Invalid value for -E\n");
            return 1;
        }
        if (value < 1) {
            printf("Value for -E must be greater than 0\n");
            return 1;
        }
        run_exp_mode(value);
        return 0;

    } else {
        // Report error due to unknown parameter.
        fprintf(stderr, "Unknown parameter: %s\n", argv[1]);
        return 1;
    }
}