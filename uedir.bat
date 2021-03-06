@echo off
echo off

REM *** UEDIR.BAT ***

rem speedup execution under 4DOS
if "%@eval[2+2]" == "4" loadbtm on
cls
echo 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
echo  異栩   異栩  異栩?      UEDIR, Ultra Extract Directory [1.0]
echo 異  異   異   異  異     'Decompresses a complete directory structure
echo 異栩栩   異   異栩?  -NL  which was compressed by UCDIR'
echo 異  異   異   異 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
echo 異  異  異栩  異 (C) Copyright 1994, Ad Infinitum Programs, all rights reserved
echo 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?

if not exist UCDIRDAT.UC2 goto noucdir

echo 敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
set UC2_WIN=xxxxxxxxxxxxxxx > nul
if not q%UC2_WIN%==qxxxxxxxxxxxxxxx goto smallenv
set UC2_WIN=003 009 078 020
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo ?                                                                             ?
echo 青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
:smallenv
UC E -F -S UCDIRDAT
echo ?
echo 青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
set uc2_win=

if errorlevel 21 goto archerror
if errorlevel 20 goto ok
if errorlevel 1 goto archerror

:ok
echo UEDIR: All files from UCDIRDAT.UC2 have been extracted into the current
echo        directory and below. UCDIRDAT.UC2 is still present to allow UCDIR
echo        to perform much faster, the next time you use it.
attrib -r ucdirdat.uc2 > nul
goto end

:noucdir
echo UEDIR ERROR: No UCDIRDAT.UC2 found in the current directory.
goto end

:archerror
echo UEDIR ERROR: Not all files/directories have been extracted.
goto end

:end
