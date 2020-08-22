.model flat, c

.code
MmxValAdd proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 24]
  cmp eax, AddOpCount
  jae BadOp

  movq mm0, [ebp + 8]
  movq mm1, [ebp + 16]
  jmp [AddOpTable + eax*4]

EPADDB:
  paddb mm0,mm1
  jmp SaveResult
EPADDSB:
  paddsb mm0,mm1
  jmp SaveResult
EPADDUSB:
  paddusb mm0, mm1
  jmp SaveResult
EPADDW:
  paddw mm0, mm1
  jmp SaveResult
EPADDSW:
  paddsw mm0, mm1
  jmp SaveResult
EPADDUSW:
  paddusw mm0, mm1
  jmp SaveResult
EPADDD:
  nop

SaveResult:
  movd eax, mm0
  pshufw mm2, mm0, 01001110b
  movd edx, mm2

BadOp:
  pxor mm0, mm0
Done:
  emms
  pop ebp
  ret

  align 16
  AddOpTable:
    dword EPADDB, EPADDSB, EPADDUSB
    dword EPADDW, EPADDSW, EPADDUSW
    dword EPADDD
  AddOpCount equ dword ($ - AddOpTable) / sizeof dword

MmxValAdd endp
  end