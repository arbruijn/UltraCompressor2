@echo off
echo off

rem *** U2_EXARX.BAT ***

rem (C) Copyright 1994, Ad Infinitum Programs, all rights reserved

rem U2_EXARX.BAT accepts a single parameter: an archive file. It
rem decompresses all files (including hidden ones, etc.) of this archive
rem completely into the current directory. If nothing goes wrong, the files
rem U$~CHK1 and U$~CHK2 are created by this batch file. UC tests for the
rem presence of those files.

rem The 'UC ~*' command checks if files/directories are present in the
rem current directory (to check if anything at all has been extracted
rem from the archive) and creates the u$~chk1 file if this is the
rem case.

rem ***  ARX  ***

   rem Expand archive

      arx x %1

   rem Test for correct expansion

      if errorlevel 1 goto error
      uc ~*
      if not exist u$~chk1 goto error
      goto ok


:error
rem *** Error handling ***

   if exist u$~chk1 del u$~chk1
   if exist u$~chk2 del u$~chk2
   goto end


:ok
rem *** Expansion was successfull ***

   rem Create second check file to notify complete success to UC

      echo check > u$~chk2


:end
rem *** End of batchfile ***
