#!/bin/bash

readonly from=100000
readonly to=1000000
readonly step=100000

readonly MAX_RND=32767

readonly dir_name=array_tests

mkdir $dir_name

for ((i=from;i<=to;i+=step))
do
    ./generator/gener $i $MAX_RND > ./$dir_name/${i}.in
done
