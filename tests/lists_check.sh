#!/bin/bash

mkdir -p logs
touch logs/sizes_leaks_output.txt
echo '' > logs/sizes_leaks_output.txt
echo '' > logs/sizes_output.txt
echo '' > logs/lists_failed.txt
echo '' > logs/lists_tested.txt

# set -x

lists_check()
{
  local test="$1"
  shift
  local args="$@"

  OUTPUT=$(./push_swap $(cat tests/random_ints.txt) 2>&1 | ./checker_linux $(cat tests/random_ints.txt) 2>&1)
  CHECKER_OUTPUT=$(./push_swap $(cat ./tests/random_ints.txt) 2>&1 | ./checker $(cat ./tests/random_ints.txt) 2>&1)
  VAL=$(valgrind --leak-check=full --show-leak-kinds=all ./push_swap $(cat ./random_ints.txt) 2>&1)
  echo -e "\n------------------- Generated list ($test) -------------------\n"
  echo -e "\n$test\n$(cat tests/random_ints.txt | tr '\n' ' ')\n" >> logs/lists_tested.txt
  leaks=0
  checked=0

  if [[ $(echo "$VAL" | grep "All heap blocks were freed -- no leaks are possible" | wc -l) = 0 ]] ||
     [[ $(echo "$VAL" | grep "ERROR SUMMARY: 0 errors from 0 contexts " | wc -l) = 0 ]]; then
    leaks=1
  fi

  if [[ "$OUTPUT" != "OK" ]]; then
    checked=1
  fi

  if [[ $leaks = 1 && $checked = 1 ]]; then
    echo -e "\033[31mKO + LEAKS\033[0m : $test"
    echo "" >> logs/sizes_leaks_output.txt
    echo "$test failed" >> logs/sizes_leaks_output.txt
    cat random_ints.txt >> logs/lists_failed.txt
    echo "" >> logs/sizes_leaks_output.txt
    echo "$VAL" >> logs/sizes_leaks_output.txt
    echo "----------------------------------------" >> logs/sizes_leaks_output.txt
    echo "$test failed ./push_swap $args" >> logs/sizes_output.txt
    echo "" >> logs/sizes_output.txt
    echo "$OUTPUT" >> logs/sizes_output.txt
    echo "----------------------------------------" >> logs/sizes_output.txt
  elif [[ $leaks = 0 && $checked = 1 ]]; then
    echo -e "\033[31mKO\033[0m : $test"
    echo "" >> logs/sizes_output.txt
    echo "$test failed ./push_swap $args" >> logs/sizes_output.txt
    cat random_ints.txt >> logs/lists_failed.txt
    echo "" >> logs/sizes_output.txt
    echo "$OUTPUT" >> logs/sizes_output.txt
    echo "----------------------------------------" >> logs/sizes_output.txt
  elif [[ $leaks = 1 && $checked = 0 ]]; then
    echo -e "\033[31mLEAKS\033[0m : $test "
    echo "" >> logs/sizes_leaks_output.txt
    echo "$test failed ./push_swap $args" >> logs/sizes_leaks_output.txt
    cat random_ints.txt >> logs/lists_failed.txt
    echo "" >> logs/sizes_leaks_output.txt
    echo "$VAL" >> logs/sizes_leaks_output.txt
    echo "----------------------------------------" >> logs/sizes_leaks_output.txt
  else
    echo -e "RESULT : checker_linux \033[32mOK\033[0m | checker_bonus \033[32m$(echo "$CHECKER_OUTPUT")\033[0m | Total ops $(./push_swap $(cat ./random_ints.txt) 2>&1 | wc -l)"
  fi
}

tests/random_ints.sh 1 > tests/random_ints.txt
lists_check "size : 1" 1
tests/random_ints.sh 2 > tests/random_ints.txt
lists_check "size : 2" 2
tests/random_ints.sh 3 > tests/random_ints.txt
lists_check "size : 3" 3
tests/random_ints.sh 5 > tests/random_ints.txt
lists_check "size : 5" 5
tests/random_ints.sh 10 > tests/random_ints.txt
lists_check "size : 10" 10
tests/random_ints.sh 100 > tests/random_ints.txt
lists_check "size : 100" 100
tests/random_ints.sh 500 > tests/random_ints.txt
lists_check "size : 500" 500

if [ "$(grep 'failed' logs/sizes_leaks_output.txt)" > 0 ]; then
    echo ''
    echo -e '\033[31mLEAKS KO !\033[0m'
    echo 'logs/sizes_leaks_output.txt'
    echo ''; \
    grep 'failed' logs/sizes_leaks_output.txt
	else
    echo ''
    echo -e '\033[32mNo leaks, but better to\033[0m \033[31mdouble check !\033[0m'
    echo ''
fi
