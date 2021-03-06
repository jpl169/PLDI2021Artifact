#!/bin/bash

parallelism=1

while getopts j: flag
do
    case "${flag}" in
        j) parArg=${OPTARG};;
    esac
done

if [ "$parArg" -eq "$parArg" ] 2>/dev/null
then
   parallelism=$parArg
fi

echo -e "\033[1m* Building math libraries \033[0m"
make -s clean
make -s -f Makefile
echo -e "\033[1m\tBuilding done \033[0m"

echo -e "\033[1m* Performing math library overhead test \033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\t* PWLibm against GLibc math library \033[0m"
cd overheadtest/posit32/glibc
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make --silent clean

echo -e "\033[1m\t* PWLibm against Intel math library \033[0m"
cd ../intel
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make --silent clean
echo -e "\033[1m\tMath library overhead test done \033[0m"

echo -e "\033[1m* Posit32 overhead output \033[0m"
cd ../../..
python3 posit32OverheadGlibc.py
python3 posit32OverheadIntel.py
