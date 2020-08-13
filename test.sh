#!/bin/bash

diff=0
lines=$2
lines_l=$(expr $2 - 1)
echo -e "$diff" | for (( c=0; c<$2; c++ ))
do
  ./generator "$1" | ./lem-in | awk -v i_p=$3 'BEGIN{t=0; step=-1; sol=0;} \
  {if(i_p) print $0; if($0 == "") t=1; if(t) step++; \
  if(NF > 3 && $NF~/^[0-9]*[0-9]$/) sol = $NF} \
  END {print "lem-in: ", step, "generator: ", sol, "diff: ", step-sol;}' > awk_out.txt
  let -i diff+=$( tail awk_out.txt -n 1 | awk '{print $NF}')
  for pc in $(seq 1 100); do
    echo -ne "$pc%\033[0K\r"
  done
  cat awk_out.txt
  rm awk_out.txt
  if (("$c" == "$lines_l")); then
    awk -v diff="$diff" -v lines="$2" 'BEGIN{print "average diff: ", diff/lines}'
    let -i lines+=1
  fi
done | pv -pt -i0.2 -l -s$lines -w 80
