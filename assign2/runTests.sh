#!/bin/bash

calculateB() {
  N=$1
  if [ 0 -eq $(($N%2)) ]; then
    b=$(($N/2))
  elif [ 0 -eq $(($N%3)) ]; then
    b=$(($N/3))
  elif [ 0 -eq $(($N%5)) ]; then
    b=$(($N/5))
  elif [ 0 -eq $(($N%7)) ]; then
    b=$(($N/7))
  elif [ 0 -eq $((N%10)) ]; then
    b=$(($N/10))
  else
    b=1
  fi

  return $b 
}

while getopts ":abcd" opt; do
  case ${opt} in
    a)
      for i in {1..550}
      do 
        echo $i
        echo -n "$i," >> ./nonblockedijk_results.csv
        ./nonblockedijk $i >> ./nonblockedijk_results.csv
      done
      ;;
    b)
      for i in {2..550}
      do
        calculateB $i
        echo "i:$i , b:$b"
        echo -n "$i," >> ./blockedijk_results.csv
        ./blockedijk $i $b >> ./blockedijk_results.csv
      done
      ;;
    c)
      for i in {2..550}
      do
        calculateB $i
        echo "i:$i , b:$b"
        echo -n "$i," >> ./blockedkij_results.csv
        ./blockedkij $i $b >> ./blockedkij_results.csv
      done
      ;;
    d)
      for i in {1..550}
      do 
        echo $i
        echo -n "$i," >> ./blas_dgemm_results.csv
        ./blas_dgemm $i >> ./blas_dgemm_results.csv
      done
      ;;
    \?)
      echo "Usage cmd [-a] [-b] [-c] [-d]"
      ;;
  esac
done
