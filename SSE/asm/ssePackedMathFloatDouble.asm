.model flat, c

.const
align 16
AbsMaskFloat	dword 7fffffffh, 7fffffffh, 7fffffffh, 7fffffffh
AbsMaskDouble	qword 7fffffffffffffffh, 7fffffffffffffffh

; extern "C" void ssePackedMathFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
; extern "C" void ssePackedMathDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
.code
ssePackedMathFloat32 proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  movaps xmm0, [eax]
  movaps xmm1, [ecx]

  ; add a + b -> a
  movaps xmm2, xmm0
  addps xmm2, xmm1
  movaps [edx + 0], xmm2

  ; sub a - b -> a
  movaps xmm2, xmm0
  subps xmm2, xmm1
  movaps [edx + 16], xmm2

  ; mul a * b -> a
  movaps xmm2, xmm0
  mulps xmm2, xmm1
  movaps [edx + 32], xmm2

  ; div a / b -> a
  movaps xmm2, xmm0
  divps xmm2, xmm1
  movaps [edx + 48], xmm2

  ; min a, b
  movaps xmm2, xmm0
  minps xmm2, xmm1
  movaps [edx + 64], xmm2

  ; max a, b
  movaps xmm2, xmm0
  maxps xmm2, xmm1
  movaps [edx + 80], xmm2

  ; fabs b
  movaps xmm2, xmm1
  andps xmm2, AbsMaskFloat
  movaps [edx + 96], xmm2

  ; sqrt(b)
  sqrtps xmm2, xmm1
  movaps [edx + 112], xmm2

  pop ebp
  ret
ssePackedMathFloat32 endp

ssePackedMathDouble64 proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  movapd xmm0, [eax]
  movapd xmm1, [ecx]

  ; add a + b -> a
  movapd xmm2, xmm0
  addpd xmm2, xmm1
  movapd [edx + 0], xmm2

  ; sub a - b -> a
  movapd xmm2, xmm0
  subpd xmm2, xmm1
  movapd [edx + 16], xmm2

  ; mul a * b -> a
  movapd xmm2, xmm0
  mulpd xmm2, xmm1
  movapd [edx + 32], xmm2

  ; div a / b -> a
  movapd xmm2, xmm0
  divpd xmm2, xmm1
  movapd [edx + 48], xmm2

  ; min a, b
  movapd xmm2, xmm0
  minpd xmm2, xmm1
  movapd [edx + 64], xmm2

  ; max a, b
  movapd xmm2, xmm0
  maxpd xmm2, xmm1
  movapd [edx + 80], xmm2

  ; fabs b
  movapd xmm2, xmm1
  andpd xmm2, AbsMaskDouble
  movapd [edx + 96], xmm2

  ; sqrt(b)
  sqrtpd xmm2, xmm1
  movapd [edx + 112], xmm2

  pop ebp
  ret
ssePackedMathDouble64 endp

end