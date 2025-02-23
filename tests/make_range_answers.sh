#!/bin/bash

for file in *.dat; do
  if [ -f "$file" ]; then
    #echo "$file"
    answer=${file/.dat/.ans_range}
    user_answer=${file/.dat/.user_ans}
    test_num=${file/.dat/}
    echo "Test:$test_num"
    mu_command="./range_query < $file > $answer"
    echo "$mu_command"
    eval "$mu_command"  
  fi
done
