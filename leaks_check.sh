#!/bin/bash

mkdir -p logs
touch logs/valgrind_output.txt
echo '' > logs/valgrind_output.txt

valgrind_test()
{
  local test="$1"
  shift
  local args="$@"

  # echo "testing $test with args : $args"
  OUTPUT=$(valgrind --leak-check=full ./push_swap $args 2>&1)
  if [ $(echo "$OUTPUT" | grep "All heap blocks were freed -- no leaks are possible" | wc -l) -eq 0 ]; then
    echo "$test (./push_swap $args): KO"
    echo "" >> logs/valgrind_output.txt
    echo "$test failed ./push_swap $args" >> logs/valgrind_output.txt
    echo "" >> logs/valgrind_output.txt
    echo "$OUTPUT" >> logs/valgrind_output.txt
    echo "----------------------------------------" >> logs/valgrind_output.txt
  else
    echo "$test (./push_swap $args): OK"
  fi

}

valgrind_test "Empty prompt" ""
valgrind_test "INT_MAX overflow" "2147483648 1"
valgrind_test "INT_MIN underflow" "-2147483649 1"
valgrind_test "LONG_MIN" "-9223372036854775808 1"
valgrind_test "Numbers with spaces" " 2  1    3"
valgrind_test "Mixed quoted/unquoted" "\"53 54\" 5 6"
valgrind_test "Non-integer character" "54 57 g 15"
valgrind_test "Invalid number format" "45/85/45/74"
valgrind_test "Duplicate numbers" "1 2 3 2"
valgrind_test "Sorted list" "1 2 3 4 5"
valgrind_test "Single element" "42"
valgrind_test "Letters in number" "-2gfd47 1"
