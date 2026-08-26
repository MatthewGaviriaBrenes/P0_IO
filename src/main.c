// Main.c
// Entry point for program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    // Show info on how to use the program if not running with a single parameter. 
    if (argc != 2) 
    {
        printf("Usage: %s -X | -E=n\n", argv[0]);
        printf("-X : Sample Mode.\n");
        printf("-E=n : Experimental mode (100 * n cases).\n");
        return 1;
    }

    // Parse input parameter to start sample mode (-X) or experimental mode (-E=n | n: number).
    if (strcmp(argv[1], "-X") == 0) 
    {
        printf("Running in Sample mode.\n");
        // TODO: Run program in sample mode.
        return 1;
    } else if (strncmp(argv[1], "-E=", 3) == 0)
    {
        const char *e_value_input = argv[1] + 3;
        int e_value = atoi(e_value_input);

        printf("Running in Experimental mode - Input value: %s\n", e_value_input);
        // TODO: Run program in experimental mode.
        return 1;
    } else {
        // Report error due to unknown parameter.
        fprintf(stderr, "Unknown parameter: %s\n", argv[1]);
        return 1;
    }
}