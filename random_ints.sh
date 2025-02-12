
#!/bin/bash

# Set default size to 100 if no argument
size=${1:-100}

declare -A nums

while (( ${#nums[@]} < size )); do
    # Generate a 32-bit signed integer using od
    num=$(od -An -N4 -t d4 /dev/urandom | tr -d ' ')
    nums["$num"]=1
done

echo "${!nums[@]}" > random_ints.txt

