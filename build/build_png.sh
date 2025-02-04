#!/bin/bash

for file in *.dot; do
  if [ -f "$file" ]; then
    answer=${file/.dot/.png}
    mu_command="dot -Tpng $file -o $answer"
    eval "$mu_command"
#    rm "$file"
  fi
done

