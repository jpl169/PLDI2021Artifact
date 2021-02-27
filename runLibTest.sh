#!/bin/bash

parallelism=8

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
cd libtest/float/glibc
make --silent clean
make --silent
cat Comamnds.txt | parallel -j $parallelism
make clean

echo -e "\033[1m\tResult: \033[0m"
cat Exp_FGResult.txt
cat Exp2_FGResult.txt
cat Exp10_FGResult.txt
cat Log_FGResult.txt
cat Log2_FGResult.txt
cat Log10_FGResult.txt
cat Sinh_FGResult.txt
cat Cosh_FGResult.txt
echo -e "\033[1m\tPWLibm and GLibc math library test complete \033[0m"

echo -e "\033[1m\t* PWLibm against Intel math library test \033[0m"
cd ../intel
make --silent clean
make --silent
cat Commands.txt | parallel -j $parallelism
make clean

echo -e "\033[1m\tResult: \033[0m"
cat Exp_FIResult.txt
cat Exp2_FIResult.txt
cat Exp10_FIResult.txt
cat Log_FIResult.txt
cat Log2_FIResult.txt
cat Log10_FIResult.txt
cat Sinh_FIResult.txt
cat Cosh_FIResult.txt
cat Sinpi_FIResult.txt
cat Cospi_FIResult.txt
echo -e "\033[1m\tPWLibm against Intel math library test complete \033[0m"

cd ../../..
