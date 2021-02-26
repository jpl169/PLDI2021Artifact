#!/bin/bash
mkdir -p CoshPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_13.log CoshPolyInfo/Cosh_13.h 13;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_5.log CoshPolyInfo/Cosh_5.h 5;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_9.log CoshPolyInfo/Cosh_9.h 9;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_17.log CoshPolyInfo/Cosh_17.h 17 &
