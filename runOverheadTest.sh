#!/bin/bash
echo -e "\033[1m* Building math libraries \033[0m"
make -s clean
make -s
echo -e "\033[1m\tBuilding done \033[0m"

echo "Measuring float math library speed"
cd ../float
make -s clean
make -s
./runAll.sh
make -s clean

cd ../..
