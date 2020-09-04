.model flat, c

.const
align 16
AbsMaskFloat	dword 7fffffffh, 0, 0, 0
AbsMaskDouble	qword 7fffffffffffffffh, 0

; extern "C" void ssePackedMathFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
; extern "C" void ssePackedMathDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
.code
ssePackedMathFloat32 proc
  push ebp
  mov ebp, esp

  pop ebp
  ret
ssePackedMathFloat32 endp

ssePackedMathDouble64 proc
  push ebp
  mov ebp, esp

  pop ebp
  ret
ssePackedMathDouble64 endp

end