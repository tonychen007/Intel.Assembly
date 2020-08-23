.model flat, c

; extern "C" int MmxValMulSigned(MmxVal a, MmxVal b, MmxMulOps ops, MmxVal * lo, MmxVal * hi);
; return: lo - low dword 
;		  hi - high dword
;         0  - invalid ops
;         1  - success

.code
MmxValMulSigned proc
  push ebp
  mov ebp, esp

  xor eax, eax
  mov edx, [ebp + 24] ; ops
  cmp edx, MulOpCount
  jae Error

  movq mm0, [ebp + 8]
  movq mm1, [ebp + 16]
  jmp [MulOpTable + edx * 4]

EPMADDUBSW:
  pmaddubsw mm0, mm1
  movq mm2, mm0
  pxor mm1, mm1
  punpcklwd mm0, mm1    ; byte * byte, so word
  punpckhwd mm2, mm1
  jmp Done
EPMADDWD:
  pmaddwd mm0, mm1
  movq mm2, mm0
  pxor mm1, mm1
  punpckldq mm0, mm1    ; word * word, so dword
  punpckhdq mm2, mm1
  jmp Done

EPMUL:
  movq mm2, mm0
  pmullw mm0, mm1       ; low result
  pmulhw mm1, mm2       ; high result
  movq mm2, mm0
  punpcklwd mm0, mm1
  punpckhwd mm2, mm1
  jmp Done
Error:
  pxor mm0, mm0
Done:
  mov eax, [ebp + 28]
  mov edx, [ebp + 32]
  movq [eax], mm0
  movq [edx], mm2
  mov eax, 1
  mov edx, 0

  emms
  pop ebp
  ret

  align 16
  MulOpTable:
    dword EPMADDUBSW, EPMADDWD, EPMUL
  MulOpCount equ dword ($ - MulOpTable) / sizeof dword
MmxValMulSigned endp
  end