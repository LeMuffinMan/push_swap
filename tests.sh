#!/bin/bash

SIZE=${1:-100}  
TESTS=${2:-10}

KO=0

for I in $(seq 1 "$TESTS"); do
    ./random_ints.sh "$SIZE" > random_ints.txt 
    NUMBERS=$(cat random_ints.txt)
    OPS=$(./push_swap $NUMBERS | wc -l)
    RESULT=$(./push_swap $NUMBERS | ./checker_linux $NUMBERS)
    echo -e "============= Test #$I =============\nTotal ops : $OPS | checker_linux : $RESULT"
    if [ "$RESULT" = "KO" ]; then
        ((KO++))
    fi
    OPERATIONS+=($OPS)
done

SUM=0
for OPS in "${OPERATIONS[@]}"; do
    SUM=$((SUM + OPS))
done
AVERAGE=$((SUM / TESTS))

SQUARED_DIFF_SUM=0
for OPS in "${OPERATIONS[@]}"; do
    DIFF=$((OPS - AVERAGE))
    SQUARED_DIFF=$((DIFF * DIFF))
    SQUARED_DIFF_SUM=$((SQUARED_DIFF_SUM + SQUARED_DIFF))
done
VARIANCE=$((SQUARED_DIFF_SUM / TESTS))
STDDEV=$(echo "scale=2; sqrt($VARIANCE)" | bc -l)

MAX=${OPERATIONS[0]:-0}
MIN=${OPERATIONS[0]:-0}
for OPS in "${OPERATIONS[@]}"; do
    if [ "$OPS" -gt "$MAX" ]; then
        MAX=$OPS
    fi
    if [ "$OPS" -lt "$MIN" ]; then
        MIN=$OPS
    fi
done

echo -e "\n==== Results ===="
echo "List size : $SIZE"
echo "Average : $AVERAGE ops"
echo "Standard deviation : $STDDEV"
echo "Worst run : $MAX ops"
echo "Best run : $MIN ops"
echo "Success : $((100 - KO * 100 / TESTS))%"

