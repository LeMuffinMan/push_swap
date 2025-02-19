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

bonus_parsing_test()
{
    local test="$1"
    shift
    local args="$@"

    PUSH_SWAP_OUT=$(./push_swap $args 2>&1)
    CHECKER_OUT=$(echo -e "$PUSH_SWAP_OUT" | ./$CHECKER $args 2>&1)

    VALGRIND_CHECKER=$(echo -e "$PUSH_SWAP_OUT" | valgrind --leak-check=full --show-leak-kinds=all ./$CHECKER $args 2>&1)

    if ! echo "$VALGRIND_CHECKER" | grep -q "All heap blocks were freed -- no leaks are possible" || \
       ! echo "$VALGRIND_CHECKER" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts"; then
        echo -e "\033[31mKO : LEAKS !\033[0m $test valgrind ./push_swap $args | ./checker $args"
        echo "$test failed on $CHECKER" >> logs/valgrind_output_bonus.txt
        echo "$VALGRIND_CHECKER" >> logs/valgrind_output_bonus.txt
        echo "----------------------------------------" >> logs/valgrind_output_bonus.txt
    else
        echo -e "\033[32mOK\033[0m : $test ./push_swap $args | ./checker $args"
    fi
}



bonus_parsing_test "Empty prompt" ""  # no input
bonus_parsing_test "INT_MAX overflow" "2147483648 1"  # Invalid number
bonus_parsing_test "INT_MIN underflow" "-2147483649 1"  # Invalid number
bonus_parsing_test "LONG_INT" "-9223372036854775808 1"  # Invalid number
bonus_parsing_test "Numbers with spaces" " 2  1    3"  # rra\nsa\nrra\n EOF
bonus_parsing_test "Mixed quoted/unquoted" "\"2 1\" 3 4"  # sa EOF
bonus_parsing_test "Non-integer character" "54 57 g 15"  # Invalid input
bonus_parsing_test "Invalid number format" "45/85/45/74"  # Invalid input
bonus_parsing_test "Duplicate numbers" "1 2 3 2"  # Invalid input
bonus_parsing_test "Sorted list" "1 2 3 4 5"  # EOF (already sorted)
bonus_parsing_test "Single element" "42"  # EOF (no operations needed)
bonus_parsing_test "Letters in number" "-2gfd47 1"  # Invalid input

if [ "$(grep 'failed' logs/valgrind_output_bonus.txt)" > 0 ]; then
    echo ''
    echo -e '\033[31mLEAKS KO !\033[0m'
    echo 'logs/valgrind_output_bonus.txt'
    echo ''
    grep 'failed' logs/valgrind_output_bonus.txt
	else
    echo ''
    echo -e '\033[32mNo leaks, but better to\033[0m \033[31mdouble check !\033[0m'
    echo ''
	fi

