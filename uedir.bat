@echo off
echo off

REM *** UEDIR.BAT ***

rem speedup execution under 4DOS
if "%@eval[2+2]" == "4" loadbtm on
cls
echo �������������������������������������������������������������������������������
echo  ����   ����  �����      UEDIR, Ultra Extract Directory [1.0]
echo ��  ��   ��   ��  ��     'Decompresses a complete directory structure
echo ������   ��   �����  -NL  which was compressed by UCDIR'
echo ��  ��   ��   �� ��������������������������������������������������������������
echo ��  ��  ����  �� (C) Copyright 1994, Ad Infinitum Programs, all rights reserved
echo �������������������������������������������������������������������������������

if not exist UCDIRDAT.UC2 goto noucdir

echo �����������������������������������������������������������������������������Ŀ
set UC2_WIN=xxxxxxxxxxxxxxx > nul
if not q%UC2_WIN%==qxxxxxxxxxxxxxxx goto smallenv
set UC2_WIN=003 009 078 020
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �                                                                             �
echo �������������������������������������������������������������������������������
:smallenv
UC E -F -S UCDIRDAT
echo �
echo �������������������������������������������������������������������������������
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
