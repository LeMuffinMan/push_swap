#!/bin/bash

# set -x

mkdir -p logs
touch logs/valgrind_output_bonus.txt 
touch logs/checker_output_bonus.txt

echo '' > logs/valgrind_output_bonus.txt
echo '' > logs/checker_output_bonus.txt
CHECKER="checker"

if [ ! -f "$CHECKER" ]; then
    echo -e "\033[31mChecker introuvable !\033[0m"
    exit 1
fi

valgrind_test()
{
    local test="$1"
    shift
    local args="$@"

    VOUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all ./push_swap $args 2>&1)

    if echo "$VOUTPUT" | grep -q "All heap blocks were freed -- no leaks are possible" && \
       echo "$VOUTPUT" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts"; then
        echo -e "\033[32mOK\033[0m : $test ./push_swap $args"
    else
        echo -e "\033[31mKO : LEAKS !\033[0m $test valgrnd ./push_swap $args"
        echo "$test failed ./push_swap $args" >> logs/valgrind_output_bonus.txt
        echo "$VOUTPUT" >> logs/valgrind_output_bonus.txt
        echo "----------------------------------------" >> logs/valgrind_output_bonus.txt
    fi

    PUSH_SWAP_OUT=$(./push_swap $args 2>&1)
    CHECKER_OUT=$(echo -e "$PUSH_SWAP_OUT" | ./$CHECKER $args 2>&1)

    VALGRIND_CHECKER=$(echo -e "$PUSH_SWAP_OUT" | valgrind --leak-check=full --show-leak-kinds=all ./$CHECKER $args 2>&1)

    if ! echo "$VALGRIND_CHECKER" | grep -q "All heap blocks were freed -- no leaks are possible" || \
       ! echo "$VALGRIND_CHECKER" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts"; then
        echo -e "\033[31mKO : LEAKS !\033[0m $test valgrind ./push_swap $args | ./checker $args"
        echo "$test failed on $CHECKER" >> logs/valgrind_output_bonus.txt
        echo "$VALGRIND_CHECKER" >> logs/valgrind_output_bonus.txt
        echo "----------------------------------------" >> logs/valgrind_output_bonus.txt
    fi
}

valgrind_test "Empty prompt" ""  # no input
valgrind_test "INT_MAX overflow" "2147483648 1"  # Invalid number
valgrind_test "INT_MIN underflow" "-2147483649 1"  # Invalid number
valgrind_test "LONG_INT" "-9223372036854775808 1"  # Invalid number
valgrind_test "Numbers with spaces" " 2  1    3"  # rra\nsa\nrra\n EOF
valgrind_test "Mixed quoted/unquoted" "\"2 1\" 3 4"  # sa EOF
valgrind_test "Non-integer character" "54 57 g 15"  # Invalid input
valgrind_test "Invalid number format" "45/85/45/74"  # Invalid input
valgrind_test "Duplicate numbers" "1 2 3 2"  # Invalid input
valgrind_test "Sorted list" "1 2 3 4 5"  # EOF (already sorted)
valgrind_test "Single element" "42"  # EOF (no operations needed)
valgrind_test "Letters in number" "-2gfd47 1"  # Invalid input


