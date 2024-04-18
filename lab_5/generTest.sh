#!/bin/bash

readonly from=1000000
readonly to=1000000
readonly step=1000000

readonly MAX_RND=32767
readonly type=2
readonly dir_name=array_tests_float
readonly name=float

mkdir $dir_name

for ((i=from;i<=to;i+=step))
do
    ./generator/gener $i $MAX_RND $type> ./$dir_name/${name}.in
done
