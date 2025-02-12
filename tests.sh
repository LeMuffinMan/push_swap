
#!/bin/bash

if [ -z "$1" ]; then
    set -- 100  
fi

if [ -z "$2" ]; then
    set -- "$1" 10 
fi

operations=()

KO=0
for i in $(seq 1 "$2"); do
    ./random_ints.sh "$1"  
    echo -e "============= Test #$i =============\nTotal ops : $(./push_swap $(cat random_ints.txt) | wc -l) | checker_linux : $(./push_swap $(cat random_ints.txt) | ./checker_linux $(cat random_ints.txt))"
    if [ $(./push_swap $(cat random_ints.txt) | ./checker_linux $(cat random_ints.txt)) = "KO" ]; then
        ((KO++))
    fi
    ops=$(./push_swap $(cat random_ints.txt) | wc -l)
    operations+=($ops)
done

sum=0
for ops in "${operations[@]}"; do
    sum=$((sum + ops))
done
average=$((sum / ${#operations[@]}))

squared_diff_sum=0
for ops in "${operations[@]}"; do
    diff=$((ops - average))
    squared_diff=$((diff * diff))
    squared_diff_sum=$((squared_diff_sum + squared_diff))
done
variance=$((squared_diff_sum / ${#operations[@]}))
stddev=$(echo "scale=2; sqrt($variance)" | bc)

max=${operations[0]}
min=${operations[0]}
for ops in "${operations[@]}"; do
    if [ "$ops" -gt "$max" ]; then
        max=$ops
    fi
    if [ "$ops" -lt "$min" ]; then
        min=$ops
    fi
done

echo -e "\n==== Résultats ===="
echo "Average : $average"
echo "Standard deviation : $stddev"
echo "worst : $max"
echo "best : $min"
echo "KO : $KO"
