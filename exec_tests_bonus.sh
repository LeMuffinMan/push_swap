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




if [ "$(echo -en "pb\nra\nsa\npa\n" | ./$CHECKER 2 1)" = "KO" ] &&
   (echo -en "pb\nra\nsa\npa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "pb\nra\nsa\npa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with invalid input  | ./$CHECKER 2 1"
elif [ "$(echo -en "pb\nra\nsa\npa\n" | ./$CHECKER 2 1)" = "KO" ] &&
   !(echo -en "pb\nra\nsa\npa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "pb\nra\nsa\npa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input  | ./$CHECKER 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input  | ./$CHECKER 2 1"
fi

if [ "$(echo -en "pb\npb\nsa\n" | ./$CHECKER 2 1)" = "KO" ] &&
   !(echo -en "pb\npb\nsa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "pb\npb\nsa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input | ./$CHECKER 2 1"
elif [ "$(echo -en "pb\npb\nsa\n" | ./$CHECKER 2 1)" = "KO" ] &&
   (echo -en "pb\npb\nsa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "pb\npb\nsa\n" | valgrind --check-leaks=full ./$CHECKER 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with invalid input | ./$CHECKER 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input | ./$CHECKER 2 1"
fi

if [ "$(echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | ./$CHECKER 4 3 2 1)" = "KO" ] &&
   !(echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | valgrind --check-leaks=full ./$CHECKER 4 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | valgrind --check-leaks=full ./$CHECKER 4 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with invalid input | ./$CHECKER 4 3 2 1"
elif [ "$(echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | ./$CHECKER 4 3 2 1)" = "KO" ] &&
   (echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | valgrind --check-leaks=full ./$CHECKER 4 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "ra\npb\npb\nra\nsa\nrra\npa\npa\n" | valgrind --check-leaks=full ./$CHECKER 4 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with invalid input | ./$CHECKER 4 3 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with invalid input | ./$CHECKER 4 3 2 1"
fi

if [ "$(echo -en "ra\n" | ./$CHECKER 3 1 2)" = "OK" ] &&
   !(echo -en "ra\n" | valgrind --check-leaks=full ./$CHECKER 3 1 2 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "ra\n" | valgrind --check-leaks=full ./$CHECKER 3 1 2 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input : ra | ./$CHECKER 3 1 2"
elif [ "$(echo -en "ra\n" | ./$CHECKER 3 1 2)" = "OK" ] &&
   (echo -en "ra\n" | valgrind --check-leaks=full ./$CHECKER 3 1 2 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "ra\n" | valgrind --check-leaks=full ./$CHECKER 3 1 2 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with valid input : ra | ./$CHECKER 3 1 2"
else
    echo -e "\033[31mKO\033[0m : unsorted list with valid input : ra | ./$CHECKER 3 1 2"
fi

if [ "$(echo -en "ra\nsa\n" | ./$CHECKER 3 2 1)" = "OK" ] &&
   !(echo -en "ra\nsa\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "ra\nsa\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input : ra sa | ./$CHECKER 3 2 1"
elif [ "$(echo -en "ra\nsa\n" | ./$CHECKER 3 2 1)" = "OK" ] &&
   (echo -en "ra\nsa\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "ra\nsa\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with valid input : ra sa | ./$CHECKER 3 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with valid input : ra sa | ./$CHECKER 3 2 1"
fi

if [ "$(echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | ./$CHECKER 5 4 3 2 1)" = "OK" ] &&
   !(echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | valgrind --check-leaks=full ./$CHECKER 5 4 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | valgrind --check-leaks=full ./$CHECKER 5 4 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : unsorted list with valid input : ra pb pb rb sa rra pa pa rra rra | ./$CHECKER 5 4 3 2 1"
elif [ "$(echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | ./$CHECKER 5 4 3 2 1)" = "OK" ] &&
   (echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | valgrind --check-leaks=full ./$CHECKER 5 4 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "ra\npb\npb\nrb\nsa\nrra\npa\npa\nrra\nrra\n" | valgrind --check-leaks=full ./$CHECKER 5 4 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : unsorted list with valid input : ra pb pb rb sa rra pa pa rra rra | ./$CHECKER 5 4 3 2 1"
else
    echo -e "\033[31mKO\033[0m : unsorted list with valid input : ra pb pb rb sa rra pa pa rra rra | ./$CHECKER 5 4 3 2 1"
fi

if [ "$(echo -en "ra\nsa" | ./$CHECKER 3 2 1 2>&1)" = "Error" ] &&
   !(echo -en "ra\nsa" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "ra\nsa" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : no final /n | ./$CHECKER 3 2 1"
elif [ "$(echo -en "ra\nsa" | ./$CHECKER 3 2 1 2>&1)" = "Error" ] &&
   (echo -en "ra\nsa" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "ra\nsa" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : no final /n | ./$CHECKER 3 2 1"
else
    echo -e "\033[31mKO\033[0m : no final /n | ./$CHECKER 3 2 1"
fi

if [ "$(echo -en "pb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   !(echo -en "pb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "pb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : B stack not empty | ./$CHECKER 3 2 1"
elif [ "$(echo -en "pb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   (echo -en "pb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "pb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : B stack not empty | ./$CHECKER 3 2 1"
else
    echo -e "\033[31mKO\033[0m : B stack not empty | ./$CHECKER 3 2 1"
fi

if [ "$(echo -en "rb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   !(echo -en "rb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "rb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : rotate an empty stack | ./$CHECKER 3 2 1"
elif [ "$(echo -en "rb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   (echo -en "rb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "rb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : rotate an empty stack | ./$CHECKER 3 2 1"
else
    echo -e "\033[31mKO\033[0m : rotate an empty stack | ./$CHECKER 3 2 1"
fi

if [ "$(echo -en "rrb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   !(echo -en "rrb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "rrb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : reverse rotate an empty stack | ./$CHECKER 3 2 1"
elif [ "$(echo -en "rrb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   (echo -en "rrb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
     echo -en "rrb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : reverse rotate an empty stack | ./$CHECKER 3 2 1"
else
    echo -e "\033[31mKO\033[0m : reverse rotate an empty stack | ./$CHECKER 3 2 1"
fi

if [ "$(echo -en "sb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   !(echo -en "sb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "sb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[32mOK\033[0m : swap an empty stack | ./$CHECKER 3 2 1"
elif [ "$(echo -en "sb\n" | ./$CHECKER 3 2 1)" = "KO" ] &&
   (echo -en "sb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "All heap blocks were freed -- no leaks are possible" || 
    echo -en "sb\n" | valgrind --check-leaks=full ./$CHECKER 3 2 1 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts")
then
    echo -e "\033[31mLEAKS\033[0m : swap an empty stack | ./$CHECKER 3 2 1"
else 
    echo -e "\033[31mKO\033[0m : swap an empty stack | ./$CHECKER 3 2 1"
fi

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
