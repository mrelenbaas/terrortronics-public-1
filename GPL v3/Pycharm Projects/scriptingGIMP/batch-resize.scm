; Contact
; -------
; Title: Resize Image
; Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
; Version 0.0.0
; Date: August 7, 2023
; Copyright 2023 Bradley Elenbaas

; License: GPL v3
; ---------------
; This program is free software you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation either version 2 of the License, or (at
; your option) any later version. This program is distributed in the
; hope that it will be useful, but WITHOUT ANY WARRANTY; without even
; the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
; PURPOSE. See the GNU General Public License for more details.

; Description
; -----------
; Saves resized image.

; Parameters and Error Levels
; ---------------------------
; No parameters.
; No error levels.

; Unit Tests
; ----------
; Load the test.png and test.jpg files into GIMP, and use this script.

; Notes
; -----
; Copy this script to the following directory:
; put this script here: C:\Users\[YOUR USERNAME]\AppData\Roaming\GIMP\2.10\scripts

(define (batch-resize pattern)
    (let*
        ((filelist (cadr (file-glob pattern 1))))
        (while (not (null? filelist))
            (let* (
                    (filename (car filelist))
                    (image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
                    (drawable   (car (gimp-image-active-drawable image)))
                    (cur-width  (car (gimp-image-width image)))
                    (cur-height (car (gimp-image-height image)))
                    (width      (* 0.25 cur-width))
                    (height     (* 0.25 cur-height))
                )
                (gimp-message filename)
                (gimp-image-scale-full image width height INTERPOLATION-CUBIC)
                (let
                    ((nfilename (string-append "resized_" filename)))
                    (gimp-file-save RUN-NONINTERACTIVE image drawable nfilename nfilename)
                )
                (gimp-image-delete image)
            )
            (set! filelist (cdr filelist))
        )
    )
)