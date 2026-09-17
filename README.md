# Dynamic Knapsack vs Greedy Knapsack

Console-based program that solves the Knapsack problem using three algoritms:

- 1/0 Dynamic Programming Algorithm
- Simple Greedy (Select the most valuable items that fit the knapsack)
- Proportional Greedy (Select the itmes with the best value/weight ratios that fit the knapsack)

The program can run on either one of two modes:

### Demo mode:
Solves a simple case of knapsack problem using the three algorithms, with the following constraints:
- Knapsack with a capacity of 15 weight units.
- Six items generated at random.
- Value per each item between 1 and 20 units.
- Weight per each item between 1 and 7 units.

### Experimental mode:
Solves 100 different Knapsack problems a given amount of times (n) using the three algorithms.

Each Knapsack problem has the following constraints:
- Knapsack weight capacities ranging from 100 to 1000 in steps of 100.
- Available item count ranging from 10 to 100 in steps of 10.

Each Knapsack problem is solved a given amount of times (`n`). For each `1..n` iteration, the available items are generated at random with the following constraints:
- Value per item between 1 and 100.
- Weight per item between 1 and 40% of the Knapsack's weight capacity for a problem (e.g. 40 if Knapsack capacity is 100.)

### Output of results
The program outputs the results in a LaTeX file and a PDF file (compiled from the LaTeX file). Additional metadata about the execution is included:

- Execution time
- Percentage of Greedy algorithm runs finding the optimal knapsack distribution against DP runs (always optimal.)

## Language

C

## Requirements

- Linux operating system
- GCC
- GNU Make
- Pdflatex

## Project Structure

- `src/`- Source code
- `Makefile` - Makefile to build executable with Make.

## How to build

Use GNU Make to build the project using the project's Makefile:

`make`

## How to run

Run the executable (`knapsack_resolver.exe`) with one of the following parameters:
- `-X` : Runs in Demo mode.
- `-E=n` : Runs in Experimental mode. Replace `n` with a number greater than 0. 