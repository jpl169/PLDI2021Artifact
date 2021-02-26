#!/bin/bash
mkdir -p SinhPolyInfo

../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_12.log SinhPolyInfo/Sinh_12.h 12;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_4.log SinhPolyInfo/Sinh_4.h 4;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_8.log SinhPolyInfo/Sinh_8.h 8;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_16.log SinhPolyInfo/Sinh_16.h 16 &
