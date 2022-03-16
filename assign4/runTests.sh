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

while getopts ":abcd" opt; do
  case ${opt} in
  a)
    for i in {1..550}
    do
      calculateP $i
      echo "i:$i , P:$p"
      echo -n "$i,$p," >> ./openmpmult_results.csv
      ./openmpmult $i $p >> ./openmpmult_results.csv
    done
    ;;
  b)
    echo "Static" > ./openmpmultStatic_results.csv
    for i in {1..550}
    do
      calculateP $i
      echo "i:$i , P:$p"
      echo -n "$i,$p," >> ./openmpmultStatic_results.csv
      ./static $i $p >> ./openmpmultStatic_results.csv
    done
    ;;
  c)
    echo "Dynamic" > ./openmpmultDynamic_results.csv
    for i in {1..550}
    do
      calculateP $i
      echo "i:$i , P:$p"
      echo -n "$i,$p," >> ./openmpmultDynamic_results.csv
      ./dynamic $i $p >> ./openmpmultDynamic_results.csv
    done
    ;;
  d)
    echo "Guided" > ./openmpmultGuided_results.csv
    for i in {1..550}
    do
      calculateP $i
      echo "i:$i , P:$p"
      echo -n "$i,$p," >> ./openmpmultGuided_results.csv
      ./guided $i $p >> ./openmpmultGuided_results.csv
    done
    ;;
  esac
done
