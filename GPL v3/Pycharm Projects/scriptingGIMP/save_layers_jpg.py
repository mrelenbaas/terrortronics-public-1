#
# Title: save_layers_jpg file.
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
# Title: Save Layers as JPG
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version 0.0.0
# Date: August 7, 2023
# Copyright 2023 Bradley Elenbaas

# License: GPL v3
# ---------------
# The save_layers_jpg.py file saves each layer as a JPG.
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
# Saves layers as a JPG.

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
# C:\Users\[YOUR USERNAME]\AppData\Roaming\GIMP\2.10\plug-ins

from gimpfu import *
import os.path
pdb = gimp.pdb

# TODO: Remember that the file_path variable uses escaped forward
#  slashes, and cannot use the os.path.join() function. It also cannot
#  use the os.getlogin() function. As of this writing, I do not
#  understand why.
def save_layers_jpg(Image, Drawable):
  """The main function."""
  for layer in Image.layers:
    if 'Outline' in layer.name:
      continue
    if 'Background' in layer.name:
      continue
    root_file_path = os.path.splitext(Image.filename + layer.name)[0]
    root_file_path = root_file_path.split(os.sep)[-1]
    file_path = 'C:\\Users\\[YOUR USERNAME]\\Desktop\\'+root_file_path+layer.name.replace(' ', '').replace('-', '')+'.jpg'
    pdb.gimp_file_save(Image, layer, file_path, file_path)
    Image.clean_all()  # Uncomment this to avoid the save warning but YOU accept the risk of loosing work.
  
register(
    'python-fu-save_layers_jpg',
    'save_layers_jpg Save layers to JPG',
    'save_layers_jpg',
    'save_layers_jpg',
    'Bradley Elenbaas',
    '8/7/2023',
    'Save Layers as JPG',
    '*',
    [
      (PF_IMAGE, 'Image', 'Chose Image', None),
      (PF_DRAWABLE, 'Drawable', 'Chose Drawable', None)
    ],
    [],
    save_layers_jpg,
    menu='<Image>/File'
    )

main()
