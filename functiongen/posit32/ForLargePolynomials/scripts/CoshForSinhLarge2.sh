#!/bin/bash
mkdir -p CoshForSinhPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_13.log CoshForSinhPolyInfo/Cosh_13.h 13;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_5.log CoshForSinhPolyInfo/Cosh_5.h 5;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_9.log CoshForSinhPolyInfo/Cosh_9.h 9;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_17.log CoshForSinhPolyInfo/Cosh_17.h 17 &
