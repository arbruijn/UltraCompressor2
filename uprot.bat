@echo off
echo off

REM *** UPROT.BAT ***

rem speedup execution under 4DOS
if "%@eval[2+2]" == "4" loadbtm on
echo 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
echo  異栩   異栩  異栩?      UltraProtect [1.0]
echo 異  異   異   異  異     "Protect archive against deletion and basic updates"
echo 異栩栩   異   異栩?  -NL
echo 異  異   異   異 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
echo 異  異  異栩  異 (C) Copyright 1994, Ad Infinitum Programs, all rights reserved
echo 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
echo ?

if q%1==q goto usage
if not exist %1 goto ext

REM no BASIC updates
echo q > u$~nobas.lck

REM no DELETE
echo q > u$~nodel.lck

uc ai %1 u$~nobas.lck u$~nodel.lck > nul

if errorlevel 1 goto errl

echo UPROT: %1 has been protected against deletion and basic updates

goto end

:ext
if not exist %1.UC2 goto noaerror

echo q > u$~nobas.lck
echo q > u$~nodel.lck

uc ai %1.uc2 u$~nobas.lck u$~nodel.lck > nul

if errorlevel 1 goto errl

echo UPROT: %1.UC2 has been protected against deletion and basic updates

goto end

:usage
echo Usage: UPROT arch
goto end

:noaerror
echo UPROT ERROR: Cannot find archive
goto end

:errl
echo UPROT ERROR: UC2 reported a problem
goto end

:end
if exist u$~nobas.lck del u$~nobas.lck > nul
if exist u$~nodel.lck del u$~nodel.lck > nul
echo ?
