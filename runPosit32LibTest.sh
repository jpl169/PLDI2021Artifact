#!/bin/bash

parallelism=3

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

echo -e "\033[1m* Performing math library correctness test \033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\t* PWLibm and GLibc math library correctness test \033[0m"
cd libtest/posit32/glibc
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make clean

cd ../intel
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make clean

echo -e "\033[1m\tResult: \033[0m"
cd ..
cat glibc/Log_PGResult.txt
cat intel/Log_PIResult.txt
cat glibc/Log2_PGResult.txt
cat intel/Log2_PIResult.txt
cat glibc/Log10_PGResult.txt
cat intel/Log10_PIResult.txt

cd ../..
