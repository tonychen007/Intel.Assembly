.model flat, c

; extern "C" int MmxCompare(MmxVal a, MmxVal b, MmxVal c[8]);
.code
MmxCompare proc
  push ebp
  mov ebp, esp

  ; init
  movq mm0, [ebp + 8]
  movq mm1, [ebp + 16]
  mov edx, [ebp + 24]

  ; EQ
  movq mm2, mm0
  pcmpeqw mm2, mm1
  movq [edx], mm2

  ; GT
  movq mm2, mm0
  pcmpgtw mm2, mm1
  movq [edx + 8], mm2

  emms
  pop ebp
  ret
MmxCompare endp
end