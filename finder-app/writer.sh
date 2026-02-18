#!/bin/bash

writeFile=$1
writeStr=$2

if [ $# -ne 2 ]; then
    echo "Wrong amount of parameters. Two parameters expected."
    exit 1
fi

if [ -z "$writeStr" ]; then
    echo "Passed second argument is missing or empty."
    exit 1
fi

dir=$(dirname "$writeFile")
mkdir -p "$dir"

echo "$writeStr" > "$writeFile"
if [ $? -ne 0 ]; then
    echo "Could not write to $writeFile."
    exit 1
fi
