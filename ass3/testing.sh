#!/bin/bash
# remember to chmod +x testing.sh
# this script is used to test all the puzzles at once

make clean
make

echo "Testing without deadends detection"
for FILE in ./puzzles/*.txt; do
    ./flow -q $FILE
done

echo "Testing with deadends detection"
for FILE in ./puzzles/*.txt; do
    ./flow -q -d $FILE
done