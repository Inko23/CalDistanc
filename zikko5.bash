#!/usr/bin/bash
make

declare -i i
for((i=0; $i < 5; ++i)); do
    ./opt_place.exe map10x10_o90_d50_s0.list amp10x10.map 
done