; Contact
; -------
; Title: Save Every Tab as JPG
; Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
; Version 2
; Date: August 7, 2023
; Copyright 2023 Bradley Elenbaas

; License: GPL v3
; ---------------
; The save-tabs-jpg.scm file saves each tab as a JPG.
; Copyright (C) 2023 Bradley Elenbaas (mr.elenbaas@gmail.com)
; This program is free software you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation either version 2 of the License, or (at
; your option) any later version. This program is distributed in the
; hope that it will be useful, but WITHOUT ANY WARRANTY; without even
; the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
; PURPOSE. See the GNU General Public License for more details.

; Description
; -----------
; Saves tabs as a JPG.

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
 
(define (script-fu-save-tabs-jpg)
  (let* ((i (car (gimp-image-list))) 
         (image)) 
    (while (> i 0) 
      (set! image (vector-ref (cadr (gimp-image-list)) (- i 1))) 
      (python-fu-savejpg RUN-NONINTERACTIVE
                      image 
                      (car (gimp-image-get-active-layer image))) 
      (gimp-image-clean-all image) 
      (set! i (- i 1))))) 
 
(script-fu-register "script-fu-save-tabs-jpg"
 "<Image>/File/Save Tabs as JPG"
 "Save all opened tabs as JPGs"
 "Bradley Elenbaas"
 "Bradley Elenbaas"
 "8/7/2023"
 "" 
 )