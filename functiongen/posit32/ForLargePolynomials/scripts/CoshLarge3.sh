#!/bin/bash
mkdir -p CoshPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_14.log CoshPolyInfo/Cosh_14.h 14;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_6.log CoshPolyInfo/Cosh_6.h 6;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_10.log CoshPolyInfo/Cosh_10.h 10;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_18.log CoshPolyInfo/Cosh_18.h 18 &
