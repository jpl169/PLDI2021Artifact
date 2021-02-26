#!/bin/bash

# Steps to take

#1. Build the interval generation program
echo -e "\033[1mCompiling interval genration code\033[0m"
cd IntervalGen/float
make clean
make
echo -e "\033[1mCompilation finished\033[0m"

#2. Run interval generation program in parallel
echo -e "\033[1mGenerating reduced intervals. This will take a long time\033[0m"
echo -e "\033[1mRunning generation script in parallel\033[0m"
cat Commands.txt | parallel -j 2

#3. Combine sinh, cosh, sinpi, and cospi
echo -e "\033[1mCombining reduced intervals for sinh, cosh, sinpi, and cospi\033[0m"


#4. Once intervals are generated, move it somewhere
echo -e "\033[1mMoving interval data file to somewhere safe...\033[0m"

#5. Finally, make clean
