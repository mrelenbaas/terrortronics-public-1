;
; Title: FPS file.
; Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
; Version: 2
; Date: September 15, 2023
;
; Intellectual Property:
; Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
;
; License:
; This file is owned by Terrortronics / Bradley Elenbaas.
; This file observes the no License.
;

;
; ------------------------------------------------------------
;
;   PureBasic - Particle
;
;    (c) Fantaisie Software
;
; ------------------------------------------------------------
;

Import ""
  time(ltime)
EndImport
Global systemtime ; Is no variable type defined, the type is automatically set to 'integer'

Procedure.l ttm ( hr, min = 0, sec = 0)
  ProcedureReturn Date ( 1970, 1, 1, hr, min, sec ) * 1000
EndProcedure


Procedure.s mtt ( num.l ) ; ///< HERE: The main function.
  ProcedureReturn FormatDate ( "%hh:%ii:%ss", num / 1000 )
EndProcedure


IncludeFile #PB_Compiler_Home + "examples/3d/Screen3DRequester.pb"
Define i, max, randomSize, startY, textureIndex, velocity, timePrevious, timeCurrent, fpsPrevious, fpsCurrent
Define.f rate
If InitEngine3D()
  Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Textures", #PB_3DArchive_FileSystem)
  InitSprite()
  InitKeyboard()
  InitMouse()
  If Screen3DRequester()
    Parse3DScripts()
    SetFrameRate(120)
    timeCurrent = time(@systemtime)
    timePrevious = timeCurrent
    timeCurrent = time(@systemtime)
    Repeat
      Screen3DEvents()
      
      timePrevious = timeCurrent
      timeCurrent = time(@systemtime)
      If timeCurrent=timePrevious
        fpsCurrent=fpsCurrent+1
      Else
        fpsPrevious=fpsCurrent
        fpsCurrent=0
        Debug fpsPrevious
      EndIf
      
      ;RenderWorld()
      ;Screen3DStats()
      FlipBuffers()
    Until KeyboardPushed(#PB_Key_Escape) Or Quit = 1
  EndIf
Else
  MessageRequester("Error", "The 3D Engine can't be initialized", 0)
EndIf
End
; IDE Options = PureBasic 6.01 LTS (Windows - x64)
; CursorPosition = 34
; FirstLine = 24
; Folding = -
; EnableXP
; DPIAware
; Executable = C:\Users\mrele\Desktop\PureBasic\Examples\3D\VGMConParticle.exe