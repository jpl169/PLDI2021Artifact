#!/bin/bash

parallelism=2

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
make -s
echo -e "\033[1m\tBuilding done \033[0m"

echo -e "\033[1m* Performing math library overhead test \033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\t* PWLibm against GLibc math library \033[0m"
cd overheadtest/float/glibc
make --silent clean
make --silent
cat Comamnds.txt | parallel -j $parallelism
make clean

echo -e "\033[1m* Performing math library overhead test \033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\t* PWLibm against Intel math library \033[0m"
cd ../intel
make --silent clean
make --silent
cat Comamnds.txt | parallel -j $parallelism
make clean

