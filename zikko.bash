#!/usr/bin/bash
make \

#declare -i i
#for((i=0; $i < 5; ++i)); do
#    ./opt_place.exe map10x10_o90_d50_s0.list map10x10.map -s 
#done


echo 0|./opt_place.exe map10x15_o90_d50_s0.list map10x15.map -s 

echo 1|./opt_place.exe map10x15_o90_d50_s0.list map10x15.map -s 

echo 2|./opt_place.exe map10x15_o90_d50_s0.list map10x15.map -s 

echo 3|./opt_place.exe map10x15_o90_d50_s0.list map10x15.map -s 

echo 4|./opt_place.exe map10x15_o90_d50_s0.list map10x15.map -s 

echo 0|./opt_place.exe map10x15_o80_d50_s0.list map10x15.map -s 

echo 1|./opt_place.exe map10x15_o80_d50_s0.list map10x15.map -s 

echo 2|./opt_place.exe map10x15_o80_d50_s0.list map10x15.map -s 

echo 3|./opt_place.exe map10x15_o80_d50_s0.list map10x15.map -s 

echo 4|./opt_place.exe map10x15_o80_d50_s0.list map10x15.map -s 