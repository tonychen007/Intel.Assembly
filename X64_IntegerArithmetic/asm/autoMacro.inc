.nolist
extern __chkstk:proc

;-------------------------------------------------------------------------
; _CreateFrame
;
; Description:  The following macro generates code that creates a stack
;               frame for x86-64 functions.
;
; Macro Parameters: Prefix          Macro symbolic name prefix
;                   StkLoc1			Size in bytes for local1 vars
;                   StkLoc2			Size in bytes for XMM reg save area
;                   Rnv1 - Rnv7     Non-volatile registers to save
;-------------------------------------------------------------------------
_CreateFrame macro Prefix, StkLoc1, StkLoc2, Rnv1,Rnv2,Rnv3,Rnv4,Rnv5,Rnv6,Rnv7
.errnz StkLoc1 mod 16, <Macro parameter 'StkLoc1' must be evenly divisible by 16>
.errnz StkLoc2 mod 16, <Macro parameter 'StkLoc2' must be evenly divisible by 16>
.errnz StkLoc2 GT 240, <Macro parameter 'StkLoc2' must be less than or equal to 240>

  push rbp
  .pushreg rbp
  NumPushReg = 1

IFNB <Rnv1>
  push Rnv1
  .pushreg Rnv1
  NumPushReg = NumPushReg+1
ENDIF
IFNB <Rnv2>
  push Rnv2
  .pushreg Rnv2
  NumPushReg=NumPushReg+1
ENDIF
IFNB <Rnv3>
  push Rnv3
  .pushreg Rnv3
  NumPushReg=NumPushReg+1
ENDIF
IFNB <Rnv4>
  push Rnv4
  .pushreg Rnv4
  NumPushReg=NumPushReg+1
ENDIF
IFNB <Rnv5>
  push Rnv5
  .pushreg Rnv5
  NumPushReg=NumPushReg+1
ENDIF
IFNB <Rnv6>
  push Rnv6
  .pushreg Rnv6
  NumPushReg=NumPushReg+1
ENDIF
IFNB <Rnv7>
  push Rnv7
  .pushreg Rnv7
  NumPushReg=NumPushReg+1
ENDIF

  StkPad = ((NumPushReg AND 1) XOR 1) * 8
  StkALL = StkLoc1 + StkLoc2 + StkPad

IF (StKALL GE 4096)
  mov rax,StkALL
  call __chkstk
  sub rsp,rax
  .allocstack StkALL
ELSEIF (StkALL GT 0)
  sub rsp,StkALL
  .allocstack StkALL
ENDIF

IF (StkLoc2 GT 0)
  lea rbp,[rsp+StkLoc2]
ELSE
  mov rbp,rsp
ENDIF
  .setframe rbp,StkLoc2

; symbol, ValStackSizeTotal CATSTR <Prefix>,<StkALL> is just like a var
; whose name  is <Prefix>,<StkALL>;

  ValStackSizeTotal CATSTR <Prefix>,<StkALL>
  ValStackSizeTotal=StkALL

  ValStackSizeLocal1 CATSTR <Prefix>,<StkALL>
  ValStackSizeLocal1=StkLoc1

  ValStackSizeLocal2 CATSTR <Prefix>,<StkALL>
  ValStackSizeLocal2=StkLoc2

  ValNameOffsetHomeRCX CATSTR <Prefix>,<OffsetHomeRCX>
  ValNameOffsetHomeRCX=StkLoc1+NumPushReg*8+StkPad+8

  ValNameOffsetHomeRDX CATSTR <Prefix>,<OffsetHomeRDX>
  ValNameOffsetHomeRDX=StkLoc1+NumPushReg*8+StkPad+16

  ValNameOffsetHomeR8 CATSTR <Prefix>,<OffsetHomeR8>
  ValNameOffsetHomeR8=StkLoc1+NumPushReg*8+StkPad+24

  ValNameOffsetHomeR9 CATSTR <Prefix>,<OffsetHomeR9>
  ValNameOffsetHomeR9=StkLoc1+NumPushReg*8+StkPad+32

  ValNameOffsetStackArgs CATSTR <Prefix>,<OffsetStackArgs>
  ValNameOffsetStackArgs=StkLoc1+NumPushReg*8+StkPad+40

  ValNameOffsetSaveXmmRegs CATSTR <Prefix>,<OffsetSaveXmmRegs>
  ValNameOffsetSaveXmmRegs=StkLoc2

  ; old rxx  <- set rsp to here
  ; StkPad   <- 
  ; StkLoc1  <- rbp
  ; StkLoc2  <- rsp
  ValNameOffsetDeleteFrame CATSTR <Prefix>,<OffsetDeleteFrame>
  ValNameOffsetDeleteFrame=StkLoc1+StkPad
endm


;-------------------------------------------------------------------------
; _DeleteFrame
;
; Description:  The following macro generates code that de-allocate a
;               stack frame previously created using _CreateFrame.
;
; Macro Parameters: Rnv1 - Rnv7     Non-volatile registers to restore
;-------------------------------------------------------------------------
_DeleteFrame macro Rnv1,Rnv2,Rnv3,Rnv4,Rnv5,Rnv6,Rnv7
IF (ValNameOffsetDeleteFrame GT 0)
  lea rsp,[rbp+ValNameOffsetDeleteFrame]
ELSE
  mov rsp,rbp
ENDIF

IFNB <Rnv7>
  pop Rnv7
ENDIF
IFNB <Rnv6>
  pop Rnv6
ENDIF
IFNB <Rnv5>
  pop Rnv5
ENDIF
IFNB <Rnv4>
  pop Rnv4
ENDIF
IFNB <Rnv3>
  pop Rnv3
ENDIF
IFNB <Rnv2>
  pop Rnv2
ENDIF
IFNB <Rnv1>
  pop Rnv1
ENDIF

  pop rbp
endm


;------------------------------------------
;_EndProlog
;
;------------------------------------------
_EndProlog  macro
  .endprolog
endm


;-------------------------------------------------------------------------
; _SaveXmmRegs
;
; Description:  The following macro generates code that saves the
;               specified non-volatile registers to the local save area.
;
; Macro Parameters: Rnv1 - Rnv7     Non-volatile XMM registers to save.
;-------------------------------------------------------------------------
_SaveXmmRegs macro Rnv0,Rnv1,Rnv2,Rnv3,Rnv4,Rnv5,Rnv6,Rnv7,Rnv8,Rnv9
NUMSAVEXMM = 0

IFNB <Rnv0>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs],Rnv0
  .savexmm128 Rnv0,0
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv1>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+16],Rnv1
  .savexmm128 Rnv1,16
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv2>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+32],Rnv2
  .savexmm128 Rnv2,32
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv3>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+48],Rnv3
  .savexmm128 Rnv3,48
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv4>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+64],Rnv4
  .savexmm128 Rnv4,64
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv5>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+80],Rnv5
  .savexmm128 Rnv5,80
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv6>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+96],Rnv6
  .savexmm128 Rnv6,96
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv7>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+112],Rnv7
  .savexmm128 Rnv7,112
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv8>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+128],Rnv8
  .savexmm128 Rnv8,128
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF
IFNB <Rnv9>
  movdqa xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+144],Rnv9
  .savexmm128 Rnv9,144
  NUMSAVEXMM = NUMSAVEXMM + 1
ENDIF

.errnz (NUMSAVEXMM * 16) GT ValStackSizeLocal2, <XMM register save area is too small>
endm

;-------------------------------------------------------------------------
; _RestoreXmmRegs
;
; Description:  The following macro generates code that restores the
;               specified non-volatile registers from the local save area.
;
; Macro Parameters: Rnv1 - Rnv7     Non-volatile XMM registers to restore.
;-------------------------------------------------------------------------

_RestoreXmmRegs macro Rnv0,Rnv1,Rnv2,Rnv3,Rnv4,Rnv5,Rnv6,Rnv7,Rnv8,Rnv9
IFNB <Rnv0>
  movdqa Rnv0, xmmword ptr [rbp - ValNameOffsetSaveXmmRegs]
ENDIF
IFNB <Rnv1>
  movdqa rnv1,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+16]
ENDIF
IFNB <Rnv2>
  movdqa rnv2,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+32]
ENDIF
IFNB <Rnv3>
  movdqa rnv3,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+48]
ENDIF
IFNB <Rnv4>
  movdqa rnv4,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+64]
ENDIF
IFNB <Rnv5>
  movdqa rnv5,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+80]
ENDIF
IFNB <Rnv6>
  movdqa rnv6,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+96]
ENDIF
IFNB <Rnv7>
  movdqa rnv7,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+112]
ENDIF
IFNB <Rnv8>
  movdqa rnv8,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+128]
ENDIF
IFNB <Rnv9>
  movdqa rnv9,xmmword ptr [rbp-ValNameOffsetSaveXmmRegs+144]
ENDIF
endm

.list
.listmacro