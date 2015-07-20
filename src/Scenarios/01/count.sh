#/bin/bash

# script to count unique lines in files
# files should be ideally sorted same way


diff -w -U 0 $1 $2 | grep ^@ | wc -l

