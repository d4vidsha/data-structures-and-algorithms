#!/bin/bash
# remember to `chmod +x testing.sh`
# this script is used to test all the puzzles at once

# 1. compile the program with `Makefile`
printf "\nCompiling the program with Makefile\n"
make clean
make

# 2. For each puzzle, run the program without dead-ends detection.
printf "\nTesting without dead-ends detection\n"
for FILE in ./puzzles/*.txt; do
    ./flow -q $FILE
done

# 3. For each puzzle, run the program with dead-ends detection.
printf "\nTesting with dead-ends detection\n"
for FILE in ./puzzles/*.txt; do
    ./flow -q -d $FILE
done