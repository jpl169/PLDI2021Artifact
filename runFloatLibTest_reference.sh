#!/bin/bash

parallelism=4

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
make -s -f Makefile-reference
echo -e "\033[1m\tBuilding done \033[0m"

echo -e "\033[1m* Performing math library correctness test \033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\t* PWLibm and GLibc math library correctness test \033[0m"
cd libtest/float/glibc
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make --silent clean

cd ../intel
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make --silent clean
echo -e "\033[1m\tMath library correctness test complete \033[0m"

echo -e "\033[1m\tResult: \033[0m"
cd ..
cat glibc/Log_FGResult.txt
cat intel/Log_FIResult.txt
cat glibc/Log2_FGResult.txt
cat intel/Log2_FIResult.txt
cat glibc/Log10_FGResult.txt
cat intel/Log10_FIResult.txt
cat glibc/Exp_FGResult.txt
cat intel/Exp_FIResult.txt
cat glibc/Exp2_FGResult.txt
cat intel/Exp2_FIResult.txt
cat glibc/Exp10_FGResult.txt
cat intel/Exp10_FIResult.txt
cat glibc/Sinh_FGResult.txt
cat intel/Sinh_FIResult.txt
cat glibc/Cosh_FGResult.txt
cat intel/Cosh_FIResult.txt
cat glibc/Sinpi_FGResult.txt
cat intel/Sinpi_FIResult.txt
cat glibc/Cospi_FGResult.txt
cat intel/Cospi_FIResult.txt

cd ../..
