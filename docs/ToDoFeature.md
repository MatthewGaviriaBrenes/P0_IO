# Feature To-Do List

This list is not definitive, may change at any time.
This will be used for guidance on what needs to be implemented.

## 1 - Program base

* [X] Read "-X" parameter to start Demo mode.
* [X] Read "-E=n" parameter to start Experimental mode.
* [ ] Improve UI feedback (applicable across all the program.)

## 2 - Knapsack Items

* [ ] Data object for Knapsack item.
  * [ ] Identifier (optional)
  * [ ] Value.
  * [ ] Weight.
  * [ ] Ratio (Optional): Value/Weight.
  * [ ] Available (may be boolean or a number value - needs further review)
* [ ] Data structure for available Knapsack items.
* [ ] Functions:
  * [ ] Generate new Knapsack item with randomized value and weight (0 to max value set by params).
    * [ ] Calculate ratio (if applicable).
  * [ ] Find most valuable item in list of items, must be less or equal than weight limit.
  * [ ] Find item with best value ratio (value/weight), must be less or equal than weight limit.

## 3 - Knapsack Bag

* [ ] Data structure for Knapsack bag.
  * [ ] Max weight.
  * [ ] Available weight.
  * [ ] Added items.
  * [ ] Item count.
* [ ] Functions:
  * [ ] Add item to knapsack, update available weight.
  * [ ] Generate list of items in knapsack.

## 4 - Greedy algorithm

* [ ] Input parameters:
  * [ ] Available items to fill Knapsack.
  * [ ] Knapsack Bag's weight
* [ ] Generate Knapsack bag with given maximum weight.
* [ ] Select item to add to Knapsack bag.
  * [ ] Item with highest value in list.
  * [ ] Item must be available.
  * [ ] Less or equal to available weight in bag.
* [ ] Update available weight in bag and repeat search until no new items can be added.

## 5 - Proportional Greed algorithm

* [ ] Input parameters:
  * [ ] Available items to fill Knapsack.
  * [ ] Knapsack Bag's weight
* [ ] Generate Knapsack bag with given maximum weight.
* [ ] Select item to add to Knapsack bag.
  * [ ] Item with highest ratio in list.
  * [ ] Item must be available.
  * [ ] Less or equal to available weight in bag.
* [ ] Update available weight in bag and repeat search until no new items can be added.

## 6 - Knapsack Distribution Matrix (Important for 1/0 Knapsack DP)

* [ ] Define data structure: List of Knapsack Bags with different weights?
* [ ] ...TO BE DEFINED...

## 7 - 1/0 Knapsack DP algorithm

* [ ] Input parameters:
  * [ ] Available items to fill Knapsack.
  * [ ] Knapsack Bag's max weight.
* [ ] ... TO BE DEFINED ... (Review available info on the algorithm)

## 8 - Demo Mode

Resolves a random Knapsack problem with the following constraints:

* Max bag capacity: 15
* Items: 6
* Value for each item: 1..20
* Weight for each item: 1..7

* [ ] Run 1/0 DP algorithm.
* [ ] Run Greedy algorithm.
* [ ] Run Proportional Greedy algorithm.
* [ ] Capture execution time of each algorithm run.

## 9 - Experimental Mode

Resolves 100 * n Knapsack problems with the following constraints for each problem run:

* Max bag capacity: 100..1000
* Available Items: 10..100

For each Knapsack problem run, the available items are randomized:

* Value for each item: 1..100 (randomized)
* Weight for each item: 1..(40% of bag capacity) (randomized)

For each Knapsack problem:

* [ ] Run 1/0 DP algorithm
* [ ] Run Greedy algorithm
* [ ] Run Proportional Greedy algorithm
* [ ] Capture execution time of each algorithm run.

## 10 - Capturing execution metadata

* [ ] Track execution time of each algorithm run.
* [ ] For Experimental Mode:
  * [ ] Compare accuracy of Greedy algorithms on finding the optimal result against DP runs (always optimal.)
  * [ ] Use two tables to compile accuracy results for each Greedy algorithm (simple, proportional).

## 11 - Generate TEX file

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

## 12 - Generate PDF file

* [ ] Use generated TEX file to create PDF file (possible method: pdflatex).