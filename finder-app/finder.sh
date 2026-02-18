#!/bin/bash

filesdir=$1
searchstr=$2

if [ $# -ne 2 ]; then
    echo "Wrong amount of parameters. Two parameters expected."
    exit 1
elif [ ! -d "$filesdir" ]; then
    echo "Passed first argument is not a path to a directory."
    exit 1
fi

numFiles=$(find "$filesdir" -type f | wc -l)
numMatches=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $numFiles and the number of matching lines are $numMatches."