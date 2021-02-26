#!/bin/bash
mkdir -p CoshForSinhPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_14.log CoshForSinhPolyInfo/Cosh_14.h 14;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_6.log CoshForSinhPolyInfo/Cosh_6.h 6;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_10.log CoshForSinhPolyInfo/Cosh_10.h 10;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_18.log CoshForSinhPolyInfo/Cosh_18.h 18 &
