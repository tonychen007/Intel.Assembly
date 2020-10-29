; extern "C" double CalcSum(float a, double b, float c, double d, float e, double f);
; first 4 args are passed by xmm0 - xmm3
; remaining are passed by stack
.code
CalcSum proc
  cvtss2sd xmm0, xmm0		; a
  addsd xmm0, xmm1			; xmm0 = a + b

  cvtss2sd xmm2, xmm2		; c
  addsd xmm0, xmm2
  addsd xmm0, xmm3			; xmm0 =  c + d

  cvtss2sd xmm3, real4 ptr [rsp + 40]
  addsd xmm0, xmm3

  addsd xmm0, real8 ptr [rsp + 48]

  ret
CalcSum endp

; extern "C" double CalcDist(int x1, double x2, long long y1, double y2, float z1, short z2);
; xmm0 - xmm5 is volatile, xmm6 - xmm15 is non-volatile
; combination of int and float are passed by reg and xmm0 - xmm3 respectively
CalcDist proc
  ; dist of x
  cvtsi2sd xmm4, ecx
  subsd xmm1, xmm4
  mulsd xmm1, xmm1

  ; dist of y
  cvtsi2sd xmm5, r8
  subsd xmm3, xmm5
  mulsd xmm3, xmm3

  ; dist of z
  movss xmm0, real4 ptr [rsp + 40]
  cvtss2sd xmm0, xmm0
  movsx eax, word ptr [rsp + 48]
  cvtsi2sd xmm4, eax
  subsd xmm4, xmm0
  mulsd xmm4, xmm4

  ; sqrt(x+y+z);
  addsd xmm1, xmm3
  addsd xmm4, xmm1
  sqrtsd xmm0, xmm4

  ret
CalcDist endp
end