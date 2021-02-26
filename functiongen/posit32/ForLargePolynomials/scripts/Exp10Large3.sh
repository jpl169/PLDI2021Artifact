#!/bin/bash
mkdir -p Exp10PolyInfo

../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_10.log Exp10PolyInfo/exp10_10.h 10;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_14.log Exp10PolyInfo/exp10_14.h 14;
../Exp10Large /common/home/jpl169/intervals/Posit32Exp10Data Exp10PolyInfo/exp10_18.log Exp10PolyInfo/exp10_18.h 18 &
