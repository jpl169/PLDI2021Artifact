#!/bin/bash
mkdir -p CoshPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_12.log CoshPolyInfo/Cosh_12.h 12;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_4.log CoshPolyInfo/Cosh_4.h 4;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_8.log CoshPolyInfo/Cosh_8.h 8;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_16.log CoshPolyInfo/Cosh_16.h 16 &
