.model flat, c

; extern "C" void ssePackedAdd16(const XmmVal * a, const XmmVal * b, XmmVal c[2])
; c[0] - Signed;
; c[1] - Satutraed;

; extern "C" void ssePackedSub32(const XmmVal * a, const XmmVal * b, XmmVal c)
; c[0] - Signed double-word

; extern "C" void ssePackedSub16(const XmmVal * a, const XmmVal * b, XmmVal c[3])
; c[0] - Saturated word
; c[1] - Signed word
; c[2] - Unsigned saturated word

; extern "C" void ssePackedMul32(const XmmVal * a, const XmmVal * b, XmmVal c[2])
; c[0] - Signed;
; c[1] - Satutraed;

.code
ssePackedAdd16 proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]

  movdqa xmm0, [eax]
  movdqa xmm1, xmm0    ; xmm1 for Saturated
  movdqa xmm2, [ecx]

  paddw xmm0, xmm2
  paddsw xmm1, xmm2    ; Saturated

  movdqa [edx], xmm0
  movdqa [edx + 16], xmm1

  pop ebp
  ret
ssePackedAdd16 endp


ssePackedSub32 proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]

  ; Singed double-word
  movdqa xmm0, [eax]
  movdqa xmm1, [ecx]
  psubd xmm0, xmm1
  movdqa [edx], xmm0
 
  pop ebp
  ret
ssePackedSub32 endp


ssePackedSub16 proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]

  ; Saturated word
  movdqa xmm0, [eax]
  movdqa xmm1, [ecx]
  psubsw xmm0, xmm1
  movdqa [edx], xmm0

  ; Signed word
  movdqa xmm0, [eax]
  movdqa xmm1, [ecx]
  psubw xmm0, xmm1
  movdqa [edx + 16], xmm0

  ; Unsigned saturated word
  movdqa xmm0, [eax]
  movdqa xmm1, [ecx]
  psubusw xmm0, xmm1
  movdqa [edx + 32], xmm0

  pop ebp
  ret
ssePackedSub16 endp


ssePackedMul32 proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]

  movdqa xmm0, [eax]
  movdqa xmm1, [ecx]
  movdqa xmm2, [eax]
  
  ; low result
  pmulld xmm0, xmm1
  movdqa [edx], xmm0

  ; quad result
  pmuldq xmm2, xmm1
  movdqa [edx + 16], xmm2

  pop ebp
  ret
ssePackedMul32 endp
end