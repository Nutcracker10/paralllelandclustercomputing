#!/bin/bash

calculateP() {
  N=$1
  if [ 0 -eq $(($N%2)) ]; then
    p=$(($N/2))
  elif [ 0 -eq $(($N%3)) ]; then
    p=$(($N/3))
  elif [ 0 -eq $(($N%5)) ]; then
    p=$(($N/5))
  elif [ 0 -eq $(($N%7)) ]; then
    p=$(($N/7))
  elif [ 0 -eq $((N%10)) ]; then
    p=$(($N/10))
  else
    p=1
  fi

  return $p 
}

for i in {1..550}
do
  calculateP $i
  echo "i:$i , P:$p"
  echo -n "$i,$p," >> ./threadMult_results.csv
  ./threadMult $i $p >> ./threadMult_results.csv
done
