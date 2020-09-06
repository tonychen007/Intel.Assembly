.model flat, c

; extern "C" void ssePackedCompareFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
; extern "C" void ssePackedCompareDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
.code
ssePackedCompareFloat32 proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  movaps xmm0, [eax]
  movaps xmm1, [ecx]

  ; EQ
  movaps xmm2, xmm0
  cmpeqps xmm2, xmm1

  ; movaps is for packed single precision
  ; movdqa is for double quadword
  ; but as for the result, they are identical
  movdqa [edx], xmm2

  ; LT
  movaps xmm2, xmm0
  cmpltps xmm2, xmm1
  movdqa [edx + 16], xmm2

  ; LE
  movaps xmm2, xmm0
  cmpleps xmm2, xmm1
  movdqa [edx + 32], xmm2

  ; UNORD
  movaps xmm2, xmm0
  cmpunordps xmm2, xmm1
  movdqa [edx + 48], xmm2

  ; NE
  movaps xmm2, xmm0
  cmpneqps xmm2, xmm1
  movdqa [edx + 64], xmm2
  
  ; GE
  movaps xmm2, xmm0
  cmpnltps xmm2, xmm1
  movdqa [edx + 80], xmm2
  
  ; GT
  movaps xmm2, xmm0
  cmpnleps xmm2, xmm1
  movdqa [edx + 96], xmm2
  
  ; ORD
  movaps xmm2, xmm0
  cmpordps xmm2, xmm1
  movdqa [edx + 112], xmm2

  pop ebp
  ret
ssePackedCompareFloat32 endp

ssePackedCompareDouble64 proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  movapd xmm0, [eax]
  movapd xmm1, [ecx]

  ; EQ
  movapd xmm2, xmm0
  cmpeqpd xmm2, xmm1

  ; movaps is for packed single precision
  ; movdqa is for double quadword
  ; but as for the result, they are identical
  movdqa [edx], xmm2

  ; LT
  movapd xmm2, xmm0
  cmpltpd xmm2, xmm1
  movdqa [edx + 16], xmm2

  ; LE
  movapd xmm2, xmm0
  cmplepd xmm2, xmm1
  movdqa [edx + 32], xmm2

  ; UNORD
  movapd xmm2, xmm0
  cmpunordpd xmm2, xmm1
  movdqa [edx + 48], xmm2

  ; NE
  movapd xmm2, xmm0
  cmpneqpd xmm2, xmm1
  movdqa [edx + 64], xmm2
  
  ; GE
  movapd xmm2, xmm0
  cmpnltpd xmm2, xmm1
  movdqa [edx + 80], xmm2
  
  ; GT
  movapd xmm2, xmm0
  cmpnlepd xmm2, xmm1
  movdqa [edx + 96], xmm2
  
  ; ORD
  movapd xmm2, xmm0
  cmpordpd xmm2, xmm1
  movdqa [edx + 112], xmm2

  pop ebp
  ret
ssePackedCompareDouble64 endp

end