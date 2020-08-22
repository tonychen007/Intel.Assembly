.model flat, c

; extern "C" int MmxValShift(MmxVal a, MmxShiftOps ops, int count, MmxVal * b);
; Returns:      0 - invalid shiftOps argument
;               1 - success

.code
MmxValShift proc
  push ebp
  mov ebp, esp

  xor eax, eax
  mov edx, [ebp + 16]
  cmp edx, ShiftOpCount
  jae Error

  mov eax, 1
  movq mm0, [ebp + 8]
  movd mm1, dword ptr [ebp + 20]  ;int count, enum size is 4
  jmp [ShiftOpTable + edx * 4]

EPSLLW:
  psllw mm0, mm1
  jmp Done
EPSRLW:
  psrlw mm0, mm1
  jmp Done
EPSRAW:
  psraw mm0, mm1
  jmp Done
EPSLLD:
  pslld mm0, mm1
  jmp Done
EPSRLD:
  psrld mm0, mm1
  jmp Done
EPSRAD:
  psrad mm0, mm1
  jmp Done

Error:
  pxor mm0, mm0
Done:
  mov edx, [ebp + 24]
  movq [edx], mm0
  emms
  pop ebp
  ret

  align 16
  ShiftOpTable:
    dword EPSLLW, EPSRLW, EPSRAW
    dword EPSLLD, EPSRLD, EPSRAD
  ShiftOpCount equ dword ($ - ShiftOpTable) / sizeof dword

MmxValShift endp
  end