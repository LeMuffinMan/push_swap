#!/bin/bash

mkdir -p logs
touch logs/parsing_leaks_output.txt
touch logs/parsing_output.txt
echo '' > logs/parsing_leaks_output.txt
echo '' > logs/parsing_output.txt

# set -x

parsing_test()
{
  local test="$1"
  shift
  local args="$@"

  OUTPUT=$(./push_swap $args 2>&1 | ./checker_linux $args 2>&1)
  VAL=$(valgrind --leak-check=full --show-leak-kinds=all ./push_swap $args 2>&1)
  
  leaks=0
  checked=0

  if [[ $(echo "$VAL" | grep "All heap blocks were freed -- no leaks are possible" | wc -l) = 0 ]] || 
     [[ $(echo "$VAL" | grep "ERROR SUMMARY: 0 errors from 0 contexts " | wc -l) = 0 ]]; then
    leaks=1
  fi

  if [[ "$OUTPUT" == "OK" ]]; then
    checked=1
  fi

  if [[ $leaks = 1 && $checked = 1 ]]; then
    echo -e "\033[31mKO + LEAKS\033[0m : $test ./push_swap $args)"
    echo "" >> logs/parsing_leaks_output.txt
    echo "$test failed ./push_swap $args" >> logs/parsing_leaks_output.txt
    echo "" >> logs/parsing_leaks_output.txt
    echo "$VAL" >> logs/parsing_leaks_output.txt
    echo "----------------------------------------" >> logs/parsing_leaks_output.txt
    echo "$test failed ./push_swap $args" >> logs/parsing_output.txt
    echo "" >> logs/parsing_output.txt
    echo "$OUTPUT" >> logs/parsing_output.txt
    echo "----------------------------------------" >> logs/parsing_output.txt
  elif [[ $leaks = 0 && $checked = 1 ]]; then
    echo -e "\033[31mKO\033[0m : $test ./push_swap $args | ./checker_linux $args"
    echo "" >> logs/parsing_output.txt
    echo "$test failed ./push_swap $args" >> logs/parsing_output.txt
    echo "" >> logs/parsing_output.txt
    echo "$OUTPUT" >> logs/parsing_output.txt
    echo "----------------------------------------" >> logs/parsing_output.txt
  elif [[ $leaks = 1 && $checked = 0 ]]; then
    echo -e "\033[31mLEAKS\033[0m : $test ./push_swap $args"
    echo "" >> logs/parsing_leaks_output.txt
    echo "$test failed ./push_swap $args" >> logs/parsing_leaks_output.txt
    echo "" >> logs/parsing_leaks_output.txt
    echo "$VAL" >> logs/parsing_leaks_output.txt
    echo "----------------------------------------" >> logs/parsing_leaks_output.txt
  else
    echo -e "\033[32mOK\033[0m : $test ./push_swap $args | ./checker $args"
  fi
}

parsing_test "Empty prompt" ""
parsing_test "INT_MAX overflow" "2147483648 1"
parsing_test "INT_MIN underflow" "-2147483649 1"
parsing_test "LONG_MIN" "-9223372036854775808 1"
parsing_test "Mixed quoted/unquoted" "\"53 54\" 5 6"
parsing_test "Non-integer character" "54 57 g 15"
parsing_test "Invalid number format" "45/85/45/74"
parsing_test "Duplicate numbers" "1 2 3 2"
parsing_test "Letters in number" "-2gfd47 1"

if [ "$(./push_swap 2  1   3 2>&1 | ./checker_linux 2  1   3 2>&1)" == "OK" ]; then
  if [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 2  1    3 2>&1 | ./checker_linux 2  1    3 2>&1 | grep "All heap blocks were freed -- no leaks are possible" | wc -l) != 0 ] || 
    [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 2  1    3 2>&1 | ./checker_linux 2  1    3 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts " | wc -l) != 0 ]; then
    echo -e "\033[31mLEAKS\033[0m : spaces between args ./push_swap 2  1   3 | ./checker_linux 2  1   3"
    echo "" >> logs/parsing_leaks_output.txt
    echo "spaces between args ./push_swap 2  1   3 | ./checker_linux 2  1   3 failed"  >> logs/parsing_leaks_output.txt
    echo "" >> logs/parsing_leaks_output.txt
    echo "$(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 2  1    3 2>&1  | ./checker_linux 2  1    3 2>&1 )" >> logs/parsing_leaks_output.txt
  else
    echo -e "\033[32mOK\033[0m : spaces between args ./push_swap 2  1   3 | ./checker_linux 2  1   3"
  fi
else
    echo -e "\033[31mKO\033[0m : spaces between args ./push_swap 2  1   3 | ./checker_linux 2  1   3"
    echo "" >> logs/parsing_output.txt
    echo "spaces between args ./push_swap 2  1   3 | ./checker_linux 2  1   3" >> logs/parsing_output.txt
    echo "" >> logs/parsing_output.txt
    echo "$(./push_swap 2  1   3 2>&1 | ./checker_linux 2  1   3 2>&1 )" >> logs/parsing_output.txt
    echo "----------------------------------------" >> logs/parsing_output.txt
fi

if [ "$(./push_swap 1 2 3 4 5 2>&1 | ./checker_linux 1 2 3 4 5 2>&1)" == "OK" ]; then
  if [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 1 2 3 4 5 2>&1 | ./checker_linux 1 2 3 4 5 2>&1 | grep "All heap blocks were freed -- no leaks are possible" | wc -l) != 0 ] || 
    [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 1 2 3 4 5 2>&1 | ./checker_linux 1 2 3 4 5 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts " | wc -l) != 0 ]; then
    echo -e "\033[31mLEAKS\033[0m : sorted list ./push_swap 1 2 3 4 5 | ./checker_linux 1 2 3 4 5"
  else
    echo -e "\033[32mOK\033[0m : sorted list ./push_swap 1 2 3 4 5 | ./checker_linux 1 2 3 4 5"
  fi
else
    echo -e "\033[31mKO\033[0m : sorted list ./push_swap 1 2 3 4 5 | ./checker_linux 1 2 3 4 5"
fi

if [ "$(./push_swap 42 2>&1 | ./checker_linux 42 2>&1)" == "OK" ]; then
  if [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 42 2>&1 | ./checker_linux 42 2>&1 | grep "All heap blocks were freed -- no leaks are possible" | wc -l) != 0 ] || 
    [ $(valgrind --leak-check=full --show-leak-kinds=all ./push_swap 42 2>&1 | ./checker_linux 42 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts " | wc -l) != 0 ]; then
    echo -e "\033[31mLEAKS\033[0m : unique value ./push_swap 42 | ./checker_linux 42"
  else
    echo -e "\033[32mOK\033[0m : unique value ./push_swap 42 | ./checker_linux 42"
  fi
else
    echo -e "\033[31mKO\033[0m : unique value ./push_swap 42 | ./checker_linux 42"
fi

if [ "$(grep 'failed' logs/parsing_leaks_output.txt)" > 0 ]; then
    echo ''
    echo -e '\033[31mLEAKS KO !\033[0m'
    echo 'logs/parsing_leaks_output.txt'
    echo ''
    grep 'failed' logs/parsing_leaks_output.txt
	else
    echo ''
    echo -e '\033[32mNo leaks, but better to \033[31mdouble check !\033[0m'
    echo ''
  fi

