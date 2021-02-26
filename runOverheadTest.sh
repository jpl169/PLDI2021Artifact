#!/bin/bash
echo "Building math libraries"
make -s clean
make -s

echo "Measuring bfloat16 math library speed"
cd overheadtest/bfloat16
make -s clean
make -s
./runAll.sh
make -s clean

echo "Measuring posit16 math library speed"
cd ../posit16
make -s clean
make -s
./runAll.sh
make -s clean

echo "Measuring float math library speed"
cd ../float
make -s clean
make -s
./runAll.sh
make -s clean

cd ../..
