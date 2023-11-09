# Title: utility file.
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version: 2
# Date: September 15, 2023
#
# Intellectual Property:
# Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
#
# License:
# This file is owned by Terrortronics / Bradley Elenbaas.
# This file observes the MIT License.

import os
import pathlib
import sys

# This file is dedicated to utility functions.


def get_path() -> str:
    """Version 2. Last updated October 22nd, 2023.

    Used in these projects:
    - arcadeCabinet

    :return: The path to the current file.
    :rtype: str
    """
    path = os.path.join(
        pathlib.Path().resolve(),
        'art')
    return path


def main():
    """The main function."""
    print('get_path: {}'.format(get_path()))


if __name__ == '__main__':
    main()
