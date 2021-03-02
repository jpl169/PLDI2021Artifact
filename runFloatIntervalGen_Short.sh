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

#1. Build the interval generation program
echo -e "\033[1m* Compiling interval genration code\033[0m"
cd IntervalGen/float
make --silent clean
make --silent
echo -e "\033[1m\tCompilation finished\033[0m"

#2. Run interval generation program in parallel
echo -e "\033[1m* Generating reduced intervals. This will take a long time\033[0m"
echo -e "\033[1m\tRunning generation script in parallel\033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\tEstimated time: 30 minutes\033[0m"
cat IntGenCommandsShort.txt | parallel -j $parallelism

echo -e "\033[1m\tInterval generation complete\033[0m"

#3. Combine sinh, cosh, sinpi, and cospi
echo -e "\033[1m* Combining reduced intervals for sinh, cosh, sinpi, and cospi\033[0m"
echo -e "\033[1m\tRunning generation script in parallel\033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
cat MergeCommandsShort.txt | parallel -j $parallelism
echo -e "\033[1m\tFile merging complete\033[0m"


#4. Once intervals are generated, move it somewhere
echo -e "\033[1m* Moving interval data file to somewhere safe...\033[0m"
mkdir -p ../../intervals
mv FloatCoshData ../../intervals/
mv FloatSinhData ../../intervals/
echo -e "\033[1m\tFile transfer complete\033[0m"

#5. Finally, make clean
echo -e "\033[1m* Cleaning up\033[0m"
make --silent clean
cd ../..
echo -e "\033[1m\tCleanup complete\033[0m"
