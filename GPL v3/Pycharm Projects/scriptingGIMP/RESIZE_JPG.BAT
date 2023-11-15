REM Contact
REM -------
REM Title: Arcade Cabinet - Thumb Drive Updater
REM Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
REM Version: 2
REM Date: August 7, 2023
REM Copyright 2023 Bradley Elenbaas

REM License: GPL v3
REM ---------------
REM The RESIZE_JPG.BAT file resizes JPG files.
REM Copyright (C) 2023 Bradley Elenbaas (mr.elenbaas@gmail.com)
REM This program is free software you can redistribute it and/or modify
REM it under the terms of the GNU General Public License as published by
REM the Free Software Foundation either version 2 of the License, or (at
REM your option) any later version. This program is distributed in the
REM hope that it will be useful, but WITHOUT ANY WARRANTY; without even
REM the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
REM PURPOSE. See the GNU General Public License for more details.

REM Description
REM -----------
REM GIMP Batch script to resize JPGs in the current directory.

REM Parameters and Error Levels
REM ---------------------------
REM No parameters.
REM No error levels.

REM Unit Tests
REM ----------
REM Load the test.png and test.jpg files into GIMP, and use this script.

REM Notes
REM -----
REM Copy this script to the following directory:
REM Put this script in the same directory as the PNGs to be resized.

"C:\Program Files\GIMP 2\bin\gimp-console-2.10.exe" -b "(batch-resize \"*.JPG\")" -b "(gimp-quit 0)"