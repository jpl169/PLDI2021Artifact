#!/bin/bash
mkdir -p SinhPolyInfo

../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_13.log SinhPolyInfo/Sinh_13.h 13;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_5.log SinhPolyInfo/Sinh_5.h 5;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_9.log SinhPolyInfo/Sinh_9.h 9;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_17.log SinhPolyInfo/Sinh_17.h 17 &
