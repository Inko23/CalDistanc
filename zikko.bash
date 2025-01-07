#!/usr/bin/bash
make

declare -i i
for((i=0; $i < 5; ++i)); do
    ./opt_place.exe test.list test.map 
done