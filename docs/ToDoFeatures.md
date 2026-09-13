# Feature To-Do List

This list is not definitive, may change at any time.
This will be used for guidance on what needs to be implemented.

## 1 - Program base

* [X] Read "-X" parameter to start Demo mode.
* [X] Read "-E=n" parameter to start Experimental mode.
* [ ] Improve UI feedback (applicable across all the program.)

## 2 - Knapsack Items

* [X] Data object for Knapsack item.
  * [X] Identifier (optional)
  * [X] Value.
  * [X] Weight.
  * [X] Ratio (Optional): Value/Weight.
  * [X] Available (may be boolean or a number value - needs further review)
* [X] Data structure for available Knapsack items.
* [X] Functions:
  * [X] Generate new Knapsack item with randomized value and weight (1 to max value set by params).
    * [X] Calculate ratio (if applicable).
  * [X] Find most valuable item in item list by raw value.
  * [X] Find item with best value ratio (value/weight), must be less or equal than weight limit.

## 3 - Knapsack Bag

* [X] Data structure for Knapsack bag.
  * [X] Max weight.
  * [X] Available weight.
  * [X] Added items.
  * [X] Item count.
* [X] Functions:
  * [X] Generate Knapsack bag with given maximum weight.
  * [X] Add item to knapsack, update available weight.
  * [ ] TBD - Consider additional functions for Knapsack bag management.
  * [ ] TBD - Consider copy function to duplicate knapsack.
* [X] Capture execution time for algorithm run.

## 4 - Greedy algorithm

* [X] Input parameters:
  * [X] Available items to fill Knapsack.
  * [X] Knapsack to fill.
* [X] Select item to add to Knapsack bag.
  * [X] Item with highest value in list.
  * [X] Item must be available.
  * [X] Less or equal to available weight in bag.
* [X] Update available weight in bag and repeat search until no new items can be added.
* [X] Capture execution time for algorithm run.

## 5 - Proportional Greed algorithm

* [X] Input parameters:
  * [X] Available items to fill Knapsack.
  * [X] Knapsack Bag's weight
* [X] Generate Knapsack bag with given maximum weight.
* [X] Select item to add to Knapsack bag.
  * [X] Item with highest ratio in list.
  * [X] Item must be available.
  * [X] Less or equal to available weight in bag.
* [X] Update available weight in bag and repeat search until no new items can be added.
* [X] Capture execution time for algorithm run.

## 6 - 1/0 Knapsack DP algorithm

* [X] Input parameters:
  * [X] Available items to fill Knapsack.
  * [X] Knapsack Bag's max weight.
* [X] Implementation of DP resolution table and collection of run metadata.

## 7 - Demo Mode

Resolves a random Knapsack problem with the following constraints:

* Max bag capacity: 15
* Items: 6
* Value for each item: 1..20
* Weight for each item: 1..7

* [X] Run 1/0 DP algorithm.
* [X] Run Greedy algorithm.
* [X] Run Proportional Greedy algorithm.

## 8 - Experimental Mode

Resolves 100 * n Knapsack problems with the following constraints for each problem run:

* Max bag capacity: 100..1000
* Available Items: 10..100

For each Knapsack problem run, the available items are randomized:

* Value for each item: 1..100 (randomized)
* Weight for each item: 1..(40% of bag capacity) (randomized)

For each Knapsack problem group (100 groups):
* [X] Iteration setup for the 100*n cases.
* [X] Execution of case 1..n for each one of the 100 groups.
  * [X] Run 1/0 DP algorithm.
  * [X] Run Greedy algorithm.
  * [X] Run Proportional Greedy algorithm.
* [X] Collect average execution times for all three algorithms for the group.
* [X] Compare hit ratio of Greedy algoritm runs agains DP runs.
* [ ] Send collected information from Knapsack problem group run to TEX file. Current setup clears data after each group run to minimize memory usage.

## 9 - Generate TEX file

* [ ] Define method to generate TEX file programmatically (possible choice: libtex).
* [ ] Define baseline structure for generated TEX file.
  * [ ] Filename (e.g. "YYYYMMDD_HHMMSS.tex")
  * [ ] Headers, Sections, etc.
* [ ] Include mathematical expression of Knapsack problem.
  * [ ] One for Demo mode.
  * [ ] 100*n for Experimental mode.
* [ ] Render DP Matrix calculation table:
  * [ ] Should include colors (red/green).
* [ ] Include Greedy algorithms' accuracy tables.

## 10 - Generate PDF file

* [ ] Use generated TEX file to create PDF file (possible method: pdflatex).
