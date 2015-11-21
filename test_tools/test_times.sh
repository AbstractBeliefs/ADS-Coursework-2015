#!/bin/sh
for i in `seq 1 10`;
do
    ./CourseWork1 $1 solution.csv | grep -o -P "owejoefepwf"
done

for i in `seq 1 10`;
do
    ./CourseWork1 $1 solution.csv | grep -o -P "\d+\.\d+"
done
