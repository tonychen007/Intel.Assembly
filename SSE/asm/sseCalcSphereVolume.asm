.model flat, c

.const
r8_3			 real8 3.0
r8_4			 real8 4.0
r8_neg_1     real8 -1.0

; extern "C" void sseCalcSphereVolume(double r, double* sa, double* v);
.code
sseCalcSphereVolume proc
  push ebp
  mov ebp, esp
  sub esp, 8									; store PI

  ; check radius
  movsd xmm0, real8 ptr [ebp + 8]			; radius
  mov ecx, [ebp + 16]
  mov edx, [ebp + 20]
  xorpd xmm1, xmm1
  comisd xmm0, xmm1
  jp BadRadius								; pf = 1; NaN
  jb BadRadius


  ; surface area, use FPU to store PI
  ; 4 * PI * r * r
  movsd xmm1, xmm0
  mulsd xmm1, xmm1
  movsd xmm0, real8 ptr r8_4
  mulsd xmm0, xmm1
  fldpi
  fstp real8 ptr [ebp - 8]
  movsd xmm1, real8 ptr [ebp - 8]
  mulsd xmm0, xmm1
  movsd real8 ptr [ecx], xmm0

  ; volume
  ; 4 * PI * r * r * r / 3
  ; xmm0 now is 4 * PI * r * r
  movsd xmm1, real8 ptr [ebp + 8]
  mulsd xmm0, xmm1
  movsd xmm1, real8 ptr r8_3
  divsd xmm0, xmm1
  movsd real8 ptr [edx], xmm0
  
  jmp Done

BadRadius:
  movsd xmm0, real8 ptr r8_neg_1
  movsd real8 ptr [ecx], xmm0
  movsd real8 ptr [edx], xmm0
  mov esp, ebp
  pop ebp
  ret
Done:
  mov esp, ebp
  pop ebp
  ret
sseCalcSphereVolume endp
end