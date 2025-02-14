#!/bin/bash

size=${1:-100}

i=0
while (( i < size )); do
    echo "$(od -An -N4 -t d4 /dev/urandom | tr -d ' ')"
    ((i++))
done
