#
# Title: load_gimp_scripts file.
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
# Title: Load GIMP Scripts
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version 2
# Date: August 7, 2023
# Copyright 2023 Bradley Elenbaas

# License: GPL v3
# ---------------
# The load_gimp_scripts.py moves files from this directory to their
# destination on a users PC.
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
# Copies *.py files to the /plug-ins/ directory and copies *.scm files
# to the /scripts/ directory.

# Parameters and Error Levels
# ---------------------------
# No parameters.
# No error levels.

# Unit Tests
# ----------
# Load the test.png and test.jpg files into GIMP, and use this script.

# Notes
# -----
# TODO: Remember that shutil.copyfile() function doesn't work with the
#  os.path.join() function, but I don't know why. So... I've been
#  using escaped forward slashes. This script doesn't have the same
#  restrictions as the other GIMP script, so I'm extra stumped. Or,
#  dumb. The answer could also be that I'm just dumb.

import os
import shutil

destination_py = 'C:\\Users\\' \
                 + os.getlogin() \
                 + '\\AppData\\Roaming\\GIMP\\2.10\\plug-ins\\'
destination_scm = 'C:\\Users\\' \
                  + os.getlogin() \
                  + '\\AppData\\Roaming\\GIMP\\2.10\\scripts\\'

for root, dirs, files in os.walk(os.curdir):
    for name in files:
        if root == '.' and os.path.basename(__file__) not in name:
            if '.py' in name:
                shutil.copyfile(name, destination_py + name)
            if '.scm' in name:
                shutil.copyfile(name, destination_scm + name)

def main():
    """The main function."""
    pass
