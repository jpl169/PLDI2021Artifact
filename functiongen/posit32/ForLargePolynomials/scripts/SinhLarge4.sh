#!/bin/bash
mkdir -p SinhPolyInfo

../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_15.log SinhPolyInfo/Sinh_15.h 15;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_7.log SinhPolyInfo/Sinh_7.h 7;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_11.log SinhPolyInfo/Sinh_11.h 11;
../SinhLarge /common/home/jpl169/intervals/Posit32SinhData SinhPolyInfo/Sinh_19.log SinhPolyInfo/Sinh_19.h 19 &
