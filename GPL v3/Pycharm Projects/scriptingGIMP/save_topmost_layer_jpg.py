#
# Title: save_topmost_layer_jpg file.
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version: 2
# Date: September 15, 2023
#
# Intellectual Property:
# Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
#
# License:
# This file is owned by Terrortronics / Bradley Elenbaas.
# This file observes the GPL 3 License.
#

# Contact
# -------
# Title: Save JPG
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version 0.0.0
# Date: August 7, 2023
# Copyright 2023 Bradley Elenbaas

# License: GPL v3
# ---------------
# The save_topmost_layer_jpg.py file saves the top layer as a PNG.
# Copyright (C) 2023 Bradley Elenbaas (mr.elenbaas@gmail.com)
# This program is free software you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation either version 2 of the License, or (at
# your option) any later version. This program is distributed in the
# hope that it will be useful, but WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE. See the GNU General Public License for more details.

# Description
# -----------
# Saves the top layer as a JPG.

# Parameters and Error Levels
# ---------------------------
# No parameters.
# No error levels.

# Unit Tests
# ----------
# Load the test.png and test.jpg files into GIMP, and use this script.

# Notes
# -----
# Copy this script to the following directory:
# C:\Users\[YOUR SERNAME]\AppData\Roaming\GIMP\2.10\plug-ins

from gimpfu import *
import os
pdb = gimp.pdb

# TODO: Remember that including an underscore in this function will
#  break the GIMP scripting. As of this writing, I do not know why.
# TODO: Remember that the file_path variable uses escaped forward
#  slashes, and cannot use the os.path.join() function. It also cannot
#  use the os.getlogin() function. As of this writing, I do not
#  understand why.
def savejpg(Image, Drawable):
  """The main function."""
  root_file_path = os.path.splitext(Image.filename)[0]
  root_file_path = root_file_path.split(os.sep)[-1]
  file_path = 'C:\\Users\\[YOUR USERNAME]\\Desktop\\'+root_file_path+'.jpg'
  pdb.gimp_file_save(Image, Drawable, file_path, file_path)
  Image.clean_all()
  
register(
    'python-fu-savejpg',
    'savejpg Save top layer to JPG',
    'savejpg',
    'savejpg',
    'Bradley Elenbaas',
    '8/7/2023',
    'Save Top Layer as JPG',
    '*',
    [
      (PF_IMAGE, 'Image', 'Chose Image', None),
      (PF_DRAWABLE, 'Drawable', 'Chose Drawable', None)
    ],
    [],
    savejpg,
    menu='<Image>/File'
    )

main()