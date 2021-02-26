#!/bin/bash
mkdir -p Exp10PolyInfo

../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_13.log Exp10PolyInfo/exp10_13.h 13;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_9.log Exp10PolyInfo/exp10_9.h 9;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_17.log Exp10PolyInfo/exp10_17.h 17 &
