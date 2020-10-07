.model flat, c

.const
absMask qword 7FFFFFFFFFFFFFFFh, 7FFFFFFFFFFFFFFFh

; extern void avxScalarFloatPoint(double a, double b, double c[8]);
.code
avxScalarFloatPoint proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 24]
  vmovsd xmm0, real8 ptr [ebp + 8]
  vmovsd xmm1, real8 ptr [ebp + 16]
  
  vaddsd xmm2, xmm0, xmm1
  vsubsd xmm3, xmm0, xmm1
  vmulsd xmm4, xmm0, xmm1
  vdivsd xmm5, xmm0, xmm1
  vminsd xmm6, xmm0, xmm1
  vmaxsd xmm7, xmm0, xmm1
  vmovsd real8 ptr [eax], xmm2
  vmovsd real8 ptr [eax + 8], xmm3
  vmovsd real8 ptr [eax + 16], xmm4
  vmovsd real8 ptr [eax + 24], xmm5
  vmovsd real8 ptr [eax + 32], xmm6
  vmovsd real8 ptr [eax + 40], xmm7

  vsqrtsd xmm2, xmm0, xmm0
  vandpd xmm3, xmm1, xmmword ptr absMask
  vmovsd real8 ptr [eax + 48], xmm2
  vmovsd real8 ptr [eax + 56], xmm3

  pop ebp
  ret
avxScalarFloatPoint endp
end