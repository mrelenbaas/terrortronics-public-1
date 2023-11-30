;
; Title: Unnamed Tank Game file.
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
;   PureBasic - Tank
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

Define.f KeyX, KeyY, MouseX, MouseY
Define TxByte.a
Define Byte.a
Define receive2.s, receive3.s
Define comIndex
CompilerIf #PB_Compiler_OS = #PB_OS_Windows
  Port$ = "COM26"
CompilerElse
  Port$ = "/dev/ttyS0"
CompilerEndIf

#PlayerSpeed = 0.4
#CameraSpeed = 1

Structure s_Key
  Up.i
  Down.i
  Left.i
  Right.i
EndStructure

Structure s_Entity
  elapsedTime.f
  Key.s_Key
  MainNode.i
  TourelleNode.i
  CanonNode.i
  ShootNode.i
  ForwardNode.i
  SightNode.i
  CameraNode.i
  SightNode1.i
  CameraNode1.i
EndStructure

Structure s_Camera
  Camera.i
  Tightness.f
  CameraNode.i
  TargetNode.i
EndStructure

Structure Bullet
  Bullet.i
  numRibbon.i
  timer.f
  Direction.Vector3
  Speed.f
  Life.l
EndStructure


Macro GetNodePosition(Position, Node)
  Position\x = NodeX(Node)
  Position\y = NodeY(Node)
  Position\z = NodeZ(Node)
EndMacro

Macro SubVector3(V, V1, V2)
  V\x = V1\x - V2\x
  V\y = V1\y - V2\y
  V\z = V1\z - V2\z
EndMacro

;-Declare
Declare HandleEntity(*Entity.s_Entity)
Declare CameraTrack(*Camera.s_Camera, *Entity.s_Entity)
Declare CreatePyramide(Nb.i)
Declare Shootbullet()

;-Variables
Define Tank.s_Entity
Define Camera.s_Camera
Global NewList Bullets.Bullet()

If InitEngine3D() ; ///< HERE: The main function.
  
    InitSprite()
    InitKeyboard()
    InitMouse()
    
    Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Textures"        , #PB_3DArchive_FileSystem)
    Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Scripts"         , #PB_3DArchive_FileSystem)
    Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Packs/desert.zip", #PB_3DArchive_Zip)
  
    ;Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Textures", #PB_3DArchive_FileSystem)
    ;Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/Textures", #PB_3DArchive_FileSystem)
    Add3DArchive(#PB_Compiler_Home + "examples/3d/Data/fonts", #PB_3DArchive_FileSystem)
    ;Parse3DScripts()
    Parse3DScripts()
    
    If Screen3DRequester()
    If OpenSerialPort(0, Port$, 9600, #PB_SerialPort_NoParity, 8, 1, #PB_SerialPort_NoHandshake, 1024, 1024)
      MessageRequester("Information", "SerialPort opened with success")
    Else
      MessageRequester("Error", "Can't open the serial port: "+Port$)
    EndIf
    TxByte=0
    CreateText3D(110, "")
    Text3DColor(110, RGBA(255, 0, 0, 255))
    Text3DAlignment(110, #PB_Text3D_HorizontallyCentered)
    MoveText3D(110, 0, 50, 2)
    ScaleText3D(110, 20, 20, 20)
    *Buffer = AllocateMemory(22)
    *Pointer = *Buffer
    CopyMemoryString("\n", @*Pointer)
    receive3$ = "\n"
    
    SetFrameRate(120)
    timeCurrent = time(@systemtime)
    timePrevious = timeCurrent
    timeCurrent = time(@systemtime)
    
    WorldShadows(#PB_Shadow_Modulative, 500)
    
    ;Texture
    CreateTexture(10,128, 128)
    StartDrawing(TextureOutput(10))
    Box(10, 0, 128, 128, RGB(255, 255, 255))
    StopDrawing()
    ; Ribbon texture
    CreateTexture(11,128, 1)
    StartDrawing(TextureOutput(11))
    DrawingMode(#PB_2DDrawing_Gradient)
    BackColor(10)
    GradientColor(0.5, RGB(255, 255, 255))
    FrontColor(10)
    LinearGradient(10, 0, 128, 0)
    Box(10, 0, 128, 1)
    StopDrawing()
    
    ;-Material
    ;Tank
    CreateMaterial(10, LoadTexture(13, "Road.png"))
    
    ;Bullet
    CreateMaterial(11, TextureID(10))
    SetMaterialColor(11, #PB_Material_AmbientColor, RGB(255, 0, 0))
    ;Sol
    GetScriptMaterial(15, "Scene/GroundBlend")
    ;Pyramide
    CreateMaterial(16, LoadTexture(16, "TerrainWater000.png"))
    
    ;Ribbon
    ;GetScriptMaterial(7, "Examples/LightRibbonTrail")
    
    ;Ground
    CreatePlane(0, 100, 100, 100, 100, 100, 100)
    CreateEntity(0, MeshID(0), MaterialID(15), 0, 0, 0)
    ;EntityRenderMode(0, 0) ; Disable shadow casting for this entity as it's our plan
    CreateEntityBody(0, #PB_Entity_StaticBody)
    
    ; Mesh
    CreateCube(1, 1)
    CreateSphere(2, 0.75)
    CreateCylinder(3, 1.5, 8)
    
    ;-Corps
    CreateEntity(1, MeshID(1), MaterialID(10))
    ScaleEntity(1, 1, 2, 1)
    MoveEntity(1, 0, 1, 0)
    
    ;-Tourelle
    CreateEntity(2, MeshID(2), MaterialID(10))
    EntityRenderMode(2, 0)
    
    ;-Canon
    CreateEntity(3, MeshID(3), MaterialID(10))
    RotateEntity(3, 90, 0, 0)
    MoveEntity(3, 0, 0.0, -4)
    
    ;-Create Pyramide
    CreatePyramide(8)
    
    ;-Light
    CreateLight(0,RGB(125, 125, 125), 100, 500, 250)
    AmbientColor(RGB(95, 95, 95))
    
    ;-Fog
    Fog(RGB(128, 128, 128), 1, 0, 10000)
    
    ;-Skybox
    SkyBox("SkyboxMoon.png")
       
    ;-Camera
    CreateCamera(0, 0, 0, 100, 100)
    CameraFOV(0, 40)
    With Camera
      \Camera = 0
      \Tightness = 0.035
      ; Camera use 2 nodes
      \CameraNode = CreateNode(#PB_Any, 0, 700, 300) ; Camera position
      \TargetNode = CreateNode(#PB_Any)              ; For cameraLookAt
      AttachNodeObject(\CameraNode, CameraID(\Camera))
    EndWith
    
    CreateCamera(1, 0.1, 67, 33, 33)
    CameraFOV(1, 25)
    
    With Tank
      \Key\Down  = #PB_Key_Down
      \Key\Left  = #PB_Key_Left
      \Key\Right = #PB_Key_Right
      \Key\Up    = #PB_Key_Up
      
      \MainNode    = CreateNode(#PB_Any) ; Entity position
      \TourelleNode= CreateNode(#PB_Any,  0, 2.0,   0)
      \CanonNode   = CreateNode(#PB_Any,  0, 0.8,   0)
      \ShootNode   = CreateNode(#PB_Any,  0, 0.0,  -8)
      \SightNode   = CreateNode(#PB_Any,  0, 2.0, -12) ; For cameraLookAt
      \CameraNode  = CreateNode(#PB_Any,  0, 6.0,  15) ; Camera position
      \ForwardNode = CreateNode(#PB_Any,  0, 0.0,  -1) ; Direction normalized
      
      \SightNode1  = CreateNode(#PB_Any,  0, 1.0,   0) ; For cameraLookAt
      \CameraNode1 = CreateNode(#PB_Any,  0, 1.0,   0) ; Camera1 position
      
      AttachNodeObject(\MainNode, NodeID(\SightNode))
      AttachNodeObject(\MainNode, NodeID(\TourelleNode))
      AttachNodeObject(\MainNode, NodeID(\CameraNode))
      AttachNodeObject(\MainNode, NodeID(\ForwardNode))
      
      AttachNodeObject(\TourelleNode, NodeID(\CanonNode))
      AttachNodeObject(\CanonNode   , NodeID(\ShootNode))
      
      AttachNodeObject(\CanonNode   , NodeID(\CameraNode1))
      AttachNodeObject(\ShootNode   , NodeID(\SightNode1))
      
      AttachNodeObject(\Mainnode    , EntityID(1))
      AttachNodeObject(\TourelleNode, EntityID(2))
      AttachNodeObject(\CanonNode   , EntityID(3))
      AttachNodeObject(\CameraNode1 , CameraID(1))
      
    EndWith
    
    
    Parse3DScripts()
    rate = 0.5
    blendType = #PB_Material_AlphaBlend
    max = 8
    While i < max
      randomSize = 50; Random(60, 50)
      startY = Random(50, 0)
      LoadTexture(i, "cloud00" + i + ".png")
      CreateMaterial(i, TextureID(i))
      DisableMaterialLighting(i, 1)
      MaterialBlendingMode(i, blendType)
      CreateParticleEmitter(i, Random(512, 256), Random(512, 256), Random(150, 100), #PB_Particle_Point, 0, startY, 0)
      ParticleMaterial(i, MaterialID(i))
      ParticleSize(i, randomSize, randomSize)
      ParticleEmitterDirection(i, 0, -1, 0)
      ParticleTimeToLive(i, 250, 250)
      velocity = Random(7, 5) * -1
      ParticleVelocity(i, #PB_Particle_Velocity, velocity)
      ParticleEmissionRate(i, rate)
      ;If (i = 0) Or (i = 1) Or (i = 5) Or (i = 6) Or (i = 7) Or (i = 9) Or (i = 10) Or (i = 11) Or (i = 12) Or (i = 13)
      ;  ParticleAngle(i, 0, 360)
      ;EndIf
      i = i + 1
    Wend
    
    ;-Main loop
    ;
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
      
      If Engine3DStatus(#PB_Engine3D_CurrentFPS)
        Tank\elapsedTime = 40/Engine3DStatus(#PB_Engine3D_CurrentFPS)
      EndIf
      
      HandleEntity(@Tank)
      
      ShootBullet()
      
      CameraTrack(@Camera, @Tank)
      CameraLookAt(1, NodeX(Tank\SightNode1), NodeY(Tank\SightNode1), NodeZ(Tank\SightNode1))
      
      If ExamineKeyboard()
        If KeyboardPushed(#PB_Key_Up)
          ;i = Random(max - 1, 0)
          i = 0
          While i < max:
            randomSize = Random(100, 50)
            startY = Random(50, 0)
            LoadTexture(i, "VGM CON " + i + ".png")
            CreateMaterial(i, TextureID(i))
            DisableMaterialLighting(i, 1)
            MaterialBlendingMode(i, blendType)
            CreateParticleEmitter(i, Random(512, 256), Random(512, 256), Random(150, 100), #PB_Particle_Point, 0, startY, 0)
            ParticleMaterial(i, MaterialID(i))
            ParticleSize(i, randomSize, randomSize)
            ParticleEmitterDirection(i, 0, -1, 0)
            ParticleTimeToLive(i, 250, 250)
            velocity = Random(7, 5) * -1
            ParticleVelocity(i, #PB_Particle_Velocity, velocity)
            ParticleEmissionRate(i, rate)
            ;If (i = 0) Or (i = 1) Or (i = 5) Or (i = 6) Or (i = 7) Or (i = 9) Or (i = 10) Or (i = 11) Or (i = 12) Or (i = 13)
            ;  ParticleAngle(i, 0, 360)
            ;EndIf
            i = i + 1
          Wend
        EndIf
      EndIf
      
      
      
      buffer_length = AvailableSerialPortInput(0)
      For x=1 To buffer_length
        ReadSerialPortData(0, @Byte, 1)
        receive$ = receive$ + Chr(Byte)
        Text3DCaption(10, receive$)
        ;CopyMemoryString(@*receive, @*receive2)
        If CompareMemory(*Byte, *Pointer, 2)
        Else
          ;Print("HERE")
          receive$ = ""
        EndIf
      Next x
      CopyMemoryString(@*receive, @*receive2)
      Debug receive$
      ;receive$ = ""
      ;*receive-11
      
      RenderWorld()
      Screen3DStats()
      FlipBuffers()
    Until KeyboardPushed(#PB_Key_Escape) Or Quit = 1
  EndIf
  
Else
  MessageRequester("Error", "The 3D Engine can't be initialized",0)
EndIf

End

Procedure CreatePyramide(Nb)
  Define Ent, i, j
  Define Size.f, SizeD.f
  
  Size=1.5
  SizeD = Size + 0.01
  
  For j = 0 To Nb
    For i= 0 To Nb-j
      Ent = CreateEntity(#PB_Any, MeshID(1), MaterialID(16))
      CreateEntityBody(Ent, #PB_Entity_BoxBody, 0.1)
      ScaleEntity(Ent, Size, Size, Size)
      MoveEntity(Ent, j*(SizeD/2) + i * SizeD - 20, (SizeD/2)+(j*SizeD), -40, #PB_Absolute)
    Next i
  Next j
EndProcedure
Procedure Normalize(*V.Vector3)
  Define.f magSq, oneOverMag
  
  magSq = *V\x * *V\x + *V\y * *V\y + *V\z * *V\z
  If magsq > 0
    oneOverMag = 1.0 / Sqr(magSq)
    *V\x * oneOverMag
    *V\y * oneOverMag
    *V\z * oneOverMag
  EndIf
  
EndProcedure

Procedure AddShoot(*Entity.s_Entity)
  Define Bullet, Color = RGB(255, 0, 0)
  Define.Vector3 PosCanon, PosShoot
  
  Bullet = CreateEntity(#PB_Any, MeshID(2), MaterialID(11))
  ScaleEntity(Bullet, 0.4, 0.4, 0.4)
  CreateEntityBody(Bullet, #PB_Entity_SphereBody, 0.7, 0.1, 0.1)
  MoveEntity(Bullet, NodeX(*Entity\ShootNode), NodeY(*Entity\ShootNode), NodeZ(*Entity\ShootNode), #PB_Absolute)
  AddElement(Bullets())
  
  With Bullets()
    \Bullet = Bullet
    ;\numRibbon = CreateRibbonEffect(#PB_Any, MaterialID(7), 1, 80, 120);
    RibbonEffectColor(\numRibbon, 0, RGBA(255, 50, 0, 255), RGBA(1, 5, 255, 5))
    RibbonEffectWidth(\numRibbon, 0, 0.3, 1)
    AttachRibbonEffect(\numRibbon, EntityParentNode(\Bullet))
    
    GetNodePosition(PosCanon, *Entity\CanonNode)
    GetNodePosition(PosShoot, *Entity\ShootNode)
    SubVector3(\Direction, PosShoot, PosCanon)
    Normalize(\Direction)
    \Speed = 20
    \Life = ElapsedMilliseconds()
    ApplyEntityImpulse(\Bullet, \Direction\x * \Speed, \Direction\y * \Speed, \Direction\z * \Speed)
  EndWith
  
EndProcedure


Procedure Shootbullet()
  ForEach Bullets()
    With Bullets()
      If ElapsedMilliseconds()-Bullets()\Life>10000
        If IsEntity(\Bullet)
          FreeEntity(\Bullet)
          FreeEffect(\numRibbon)
        EndIf
        DeleteElement(Bullets(), 1)
      EndIf
    EndWith
  Next
EndProcedure


Procedure HandleEntity(*Entity.s_Entity)
  Protected.Vector3 Forward, PosMain, PosDir
  Protected Speed.f, Speed2.f, x.f, y.f
  Protected MouseX.f, MouseY.f
  Static Rot.Vector3, Trans.Vector3, Clic, AngleCanon.f, Time, FirstShort=1
  
  With *Entity
    GetNodePosition(PosMain, \MainNode)
    GetNodePosition(PosDir, \ForwardNode)
    SubVector3(Forward, PosDir, PosMain)
    
    Speed = #PlayerSpeed * \elapsedTime
    Speed2 = Speed / 2
    
    If ExamineMouse()
      MouseX = -(MouseDeltaX()/5) * \elapsedTime
      MouseY = -(MouseDeltaY()/5) * \elapsedTime
      
      AngleCanon + MouseY
      If AngleCanon>45
        AngleCanon = 45
      ElseIf AngleCanon<-3
        AngleCanon = -3
      EndIf
      
      If MouseButton(#PB_MouseButton_Left) And (ElapsedMilliseconds()-Time > 500 Or FirstShort = 1)
        FirstShort = 0
        Time = ElapsedMilliseconds()
        AddShoot(*Entity)
      EndIf
      
    EndIf
    
    If ExamineKeyboard()
      
      If KeyboardReleased(#PB_Key_F5)
        WorldDebug(#PB_World_DebugBody)
      ElseIf KeyboardReleased(#PB_Key_F6)
        WorldDebug(#PB_World_DebugEntity)
      ElseIf KeyboardReleased(#PB_Key_F7)
        WorldDebug(#PB_World_DebugNone)
      EndIf
      
      Rot\x * 0.30
      Rot\y * 0.30
      Rot\z * 0.30
      Trans\x * 0.30
      Trans\y = 0
      Trans\z * 0.30
      
      ;If KeyboardPushed(\Key\Up)
        ;Trans\x + Forward\x * Speed
        ;Trans\z + Forward\z * Speed
      ;ElseIf KeyboardPushed(\Key\Down)
        ;Trans\x + Forward\x * -Speed2
        ;Trans\z + Forward\z * -Speed2
      ;EndIf
      
      ;If KeyboardPushed(\Key\Left)
        ;Rot\y + 1.5 * \elapsedTime
      ;ElseIf KeyboardPushed(\Key\Right)
        ;Rot\y - 1.5 * \elapsedTime
      ;EndIf
      
    EndIf
        
    MoveNode(\MainNode, Trans\x, Trans\y, Trans\z)
    RotateNode(\MainNode, 0, Rot\y, 0, #PB_Relative)
    RotateNode(\TourelleNode, 0, MouseX, 0, #PB_Relative)
    RotateNode(\CanonNode, AngleCanon, 0, 0, #PB_Absolute)
    
  EndWith
EndProcedure

Procedure CameraTrack(*Camera.s_Camera, *Entity.s_Entity)
   Protected.Vector3 CameraPosition, TargetPosition
   Protected.f x, y, z

   GetNodePosition(CameraPosition, *Entity\CameraNode)
   GetNodePosition(TargetPosition, *Entity\SightNode)
   x = NodeX(*Camera\CameraNode)
   y = NodeY(*Camera\CameraNode)
   z = NodeZ(*Camera\CameraNode)
   x = (CameraPosition\x - x) *  *Camera\Tightness
   y = (CameraPosition\y - y) *  *Camera\Tightness
   z = (CameraPosition\z - z) *  *Camera\Tightness
   MoveNode(*Camera\CameraNode, x, y, z)

   x = NodeX(*Camera\TargetNode)
   y = NodeY(*Camera\TargetNode)
   z = NodeZ(*Camera\TargetNode)
   x = (TargetPosition\x - x) *  *Camera\Tightness
   y = (TargetPosition\y - y) *  *Camera\Tightness
   z = (TargetPosition\z - z) *  *Camera\Tightness
   MoveNode(*Camera\TargetNode, x, y, z)

   CameraLookAt(*Camera\Camera, NodeX(*Camera\TargetNode), NodeY(*Camera\TargetNode), NodeZ(*Camera\TargetNode))

EndProcedure
; IDE Options = PureBasic 6.01 LTS (Windows - x64)
; CursorPosition = 370
; FirstLine = 287
; Folding = --
; EnableXP
; DPIAware
; Executable = ..\..\purelibraries\Unnamed Tank Game.exe