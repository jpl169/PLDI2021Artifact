#!/bin/bash
mkdir -p SinhPolyInfo

../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_14.log SinhPolyInfo/Sinh_14.h 14;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_6.log SinhPolyInfo/Sinh_6.h 6;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_10.log SinhPolyInfo/Sinh_10.h 10;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_18.log SinhPolyInfo/Sinh_18.h 18 &
