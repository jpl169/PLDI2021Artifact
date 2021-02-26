#!/bin/bash
mkdir -p Exp10PolyInfo

../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_12.log Exp10PolyInfo/exp10_12.h 12;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_8.log Exp10PolyInfo/exp10_8.h 8;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_16.log Exp10PolyInfo/exp10_16.h 16 &
