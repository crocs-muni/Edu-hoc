#/bin/bash

# script to count unique lines in files
# files should be ideally sorted same way


MISSING=$( diff -w -U 0 $1 $2 | grep ^@ | wc -l)
TOTAL=$(cat $1 | wc -l )
echo $MISSING "messages missing" out of $TOTAL

