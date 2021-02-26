#!/bin/bash
mkdir -p CoshPolyInfo

../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_15.log CoshPolyInfo/Cosh_15.h 15;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_7.log CoshPolyInfo/Cosh_7.h 7;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_11.log CoshPolyInfo/Cosh_11.h 11;
../CoshLarge /common/home/jpl169/intervals/Posit32CoshData CoshPolyInfo/Cosh_19.log CoshPolyInfo/Cosh_19.h 19 &
