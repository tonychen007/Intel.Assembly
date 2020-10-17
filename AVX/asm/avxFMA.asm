.model flat, c


; extern "C" void avxFMA132SS(float * dst, float * src1, float * src2);
; extern "C" void avxFMA132PS(XmmVal * dst, XmmVal * src1, XmmVal * src2);

; mul dst and src2, add to src1 and save back to dst
.code
avxFMA132SS proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovss xmm0, real4 ptr [eax]
  vmovss xmm1, real4 ptr [ecx]
  vfmadd132ss xmm0, xmm1, real4 ptr [edx]

  vmovss real4 ptr [eax], xmm0
  vzeroupper
  pop ebp
  ret
avxFMA132SS endp

avxFMA132PS proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovaps xmm0, xmmword ptr [eax]
  vmovaps xmm1, xmmword ptr [ecx]
  vfmadd132ps xmm0, xmm1, xmmword ptr [edx]

  vmovaps xmmword ptr [eax], xmm0
  vzeroupper
  pop ebp
  ret
avxFMA132PS endp

; extern "C" void avxFMA231SS(float * dst, float * src1, float * src2);
; extern "C" void avxFMA231PS(XmmVal * dst, XmmVal * src1, XmmVal * src2);
; mul src1 and src2, add to dst and save back to dst

avxFMA231SS proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovss xmm0, real4 ptr [eax]
  vmovss xmm1, real4 ptr [ecx]
  vfmadd231ss xmm0, xmm1, real4 ptr [edx]

  vmovss real4 ptr [eax], xmm0
  vzeroupper
  pop ebp
  ret
avxFMA231SS endp

avxFMA231PS proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovaps xmm0, xmmword ptr [eax]
  vmovaps xmm1, xmmword ptr [ecx]
  vfmadd231ps xmm0, xmm1, xmmword ptr [edx]

  vmovaps xmmword ptr [eax], xmm0
  pop ebp
  ret
avxFMA231PS endp

end