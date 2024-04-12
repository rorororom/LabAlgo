#!/bin/bash

readonly from=0
readonly to=1000000
readonly step=10000

readonly k=5

readonly MAX_RND=2147483647

readonly dir_name=big_tests

mkdir $dir_name

for ((i=from;i<=to;i+=step))
do
        for ((j=0;j<k;j++))
        do
                ./generator/gener $i $MAX_RND > ./$dir_name/${i}_${j}.in
                ./qsort/qsort_c < ./$dir_name/${i}_${j}.in > ./$dir_name/${i}_${j}.out
        done
done
