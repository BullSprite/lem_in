#!/bin/bash

is_p=$3
lines=$2
declare -i size=lines*36
for (( c=0; c<$2; c++ ))
do
  ./generator $1 | ./lem-in | awk -v is_print=$is_p \
  'BEGIN {step = -1; sol = 0;}\
  {if (is_print) print $0; if ($0 == "") step = 0; if (step > -1) step += 1; \
  if (NF > 3 && $NF~/^[0-9]*[0-9]$/) sol = $NF} \
  END {print "lem-in: ", step-1, "generator: ", sol, "diff: ", step-1-sol}'
 done | pv -pt -i0.2 -s$size -w 80 | awk 'BEGIN {sum = 0; i = 0;} {print $0; if\
  ($0~/diff/) {sum += $NF;\
 i++;}} END{print "avg error: "sum/i}'
