#!/bin/bash
mkdir -p CoshForSinhPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_15.log CoshForSinhPolyInfo/Cosh_15.h 15;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_7.log CoshForSinhPolyInfo/Cosh_7.h 7;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_11.log CoshForSinhPolyInfo/Cosh_11.h 11;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshForSinhData CoshForSinhPolyInfo/Cosh_19.log CoshForSinhPolyInfo/Cosh_19.h 19 &
