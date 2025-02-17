#!/bin/bash

# set -x

mkdir -p logs
touch logs/exec_tests_bonus.txt.txt

echo '' > logs/valgrind_output_bonus.txt
echo '' > logs/exec_tests_bonus.txt.txt
CHECKER="checker"


bonus_checker_test() {
    local test="$1"
    local args="$2"
    local instructions="$3"
    local expected_output="$4"

    CHECKER_OUT=$(echo -n "$instructions" | ./$CHECKER $args 2>&1)
    VCHECKEROUT=$(echo -n "$instructions" | valgrind --leak-check=full --show-leak-kinds=all ./$CHECKER $args 2>&1)

    local test_valid=false
    local leaks=false

    if [ "$CHECKER_OUT" == "$expected_output" ]; then
        test_valid=true
    fi

    if ! echo "$VCHECKEROUT" | grep -q "All heap blocks were freed -- no leaks are possible" || \
       ! echo "$VCHECKEROUT" | grep -q "ERROR SUMMARY: 0 errors from 0 contexts"; then
        leaks=true
    fi

    if [ "$test_valid" = true ] && [ "$leaks" = false ]; then
        echo -e "\033[32mOK\033[0m : $test ./checker $args"
    elif [ "$test_valid" = true ] && [ "$leaks" = true ]; then
        echo -e "\033[31mKO : LEAKS !\033[0m $test ./checker $args"
        echo "$test failed (LEAKS)" >> logs/valgrind_output_bonus.txt
        echo "$VCHECKEROUT" >> logs/valgrind_output_bonus.txt
        echo "----------------------------------------" >> logs/valgrind_output_bonus.txt
    elif [ "$test_valid" = false ] && [ "$leaks" = false ]; then
        echo -e "\033[31mKO\033[0m : $test Expected: '$expected_output', Got: '$CHECKER_OUT'"
        echo "$test failed ./checker $args" >> logs/checker_output_bonus.txt
        echo "Expected: '$expected_output' | Got: '$CHECKER_OUT'" >> logs/checker_output_bonus.txt
        echo "----------------------------------------" >> logs/checker_output_bonus.txt
    else
        echo -e "\033[31mKO : LEAKS !\033[0m $test Expected: '$expected_output', Got: '$CHECKER_OUT'"
        echo "$test failed (INVALID + LEAKS)" >> logs/valgrind_output_bonus.txt
        echo "$VCHECKEROUT" >> logs/valgrind_output_bonus.txt
        echo "----------------------------------------" >> logs/valgrind_output_bonus.txt
    fi
}


  # exec tests 
bonus_checker_test "Already sorted" "1 2 3 4 5" "" "OK"
bonus_checker_test "Unsorted list with no moves" "3 2 1" "" "KO"
bonus_checker_test "Incorrect moves" "1 2 3" "xyz$(echo -n '')" "Error"



if [ "$(echo -en "pb\nra\nsa\npa\n" | ./$CHECKER 2 1)" = "KO" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input ./push_swap 2 1  | ./$CHECKER 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input ./push_swap 2 1  | ./$CHECKER 2 1"
fi
if [ "$(echo -en "pb\npb\nsa\n" | ./$CHECKER 2 1)" = "KO" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input ./push_swap 2 1  | ./$CHECKER 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input ./push_swap 2 1  | ./$CHECKER 2 1"
fi
if [ "$(echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | ./$CHECKER 4 3 2 1)" = "KO" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input ./push_swap  4 3 2 1 | ./$CHECKER 4 3 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input ./push_swap  4 3 2 1 | ./$CHECKER 4 3 2 1"
fi
if [ "$(echo -en "ra\n" | ./$CHECKER 3 1 2)" = "OK" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input ./push_swap 3 1 2 | ./$CHECKER 3 1 2"
else
    echo -e "\033[31mKO\033[0m : unsorted list with valid input ./push_swap 3 1 2 | ./$CHECKER 3 1 2"
fi
if [ "$(echo -en "ra\nsa\n" | ./$CHECKER 3 2 1)" = "OK" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input ./push_swap 3 2 1 | ./$CHECKER 3 1 2"
else
    echo -e "\033[31mKO\033[0m : unsorted list with valid input ./push_swap 3 2 1 | ./$CHECKER 3 1 2"
fi
if [ "$(echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | ./$CHECKER 5 4 3 2 1)" = "OK" ]; then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input ./push_swap 5 4 3 2 1 | ./$CHECKER 5 4 3 2 1"
else 
    echo -e "\033[31mKO\033[0m : unsorted list with valid input ./push_swap 5 4 3 2 1 | ./$CHECKER 5 4 3 2 1"
fi

# no end \n 
# b stack not empty
# VOIR PLUS !
#faire un autre script
#rendre plus clair les tests edge cases fait
#tester des instructions incorrectes
#tester liste b toujours remplie
