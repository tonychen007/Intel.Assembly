.model flat, c

.const
align 16

; Float point format:
; 31    30 - 23      22 - 0
; Sign   Exp.Bais   Fraction
; so 01111111 11111111 11111111 = 0x7FFFFFFF;

AbsMaskFloat	dword 7fffffffh, 0, 0, 0
AbsMaskDouble	qword 7fffffffffffffffh, 0

.code
; extern "C" void sseMathFloat(float a, float b, float c[8]);
; extern "C" void sseMathDouble(double a, double b, double c[8]);
sseMathFloat proc
  push ebp
  mov ebp, esp

  ; init
  movss xmm0, real4 ptr [ebp + 8]
  movss xmm1, real4 ptr [ebp + 12]
  mov eax, [ebp + 16]	; float c[8]

  ; add a + b
  movss xmm2, xmm0
  addss xmm2, xmm1
  movss real4 ptr [eax], xmm2

  ; sub a - b
  movss xmm2, xmm0
  subss xmm2, xmm1
  movss real4 ptr [eax + 4], xmm2

  ; mul a * b
  movss xmm2, xmm0
  mulss xmm2, xmm1
  movss real4 ptr [eax + 8], xmm2

  ; div a / b
  movss xmm2, xmm0
  divss xmm2, xmm1
  movss real4 ptr [eax + 12], xmm2

  ; min
  movss xmm2, xmm0
  minss xmm2, xmm1
  movss real4 ptr [eax + 16], xmm2
  
  ; max
  movss xmm2, xmm0
  maxss xmm2, xmm1
  movss real4 ptr [eax + 20], xmm2

  ; fabs abs(b)
  movss xmm2, xmm1
  andps xmm2, AbsMaskFloat
  movss real4 ptr [eax + 24], xmm2

  ; sqrt sqrt(fabs(b))
  sqrtss xmm2, xmm2
  movss real4 ptr [eax + 28], xmm2

  pop ebp
  ret
sseMathFloat endp

sseMathDouble proc
  push ebp
  mov ebp, esp

    ; init
  movsd xmm0, real8 ptr [ebp + 8]
  movsd xmm1, real8 ptr [ebp + 16]
  mov eax, [ebp + 24]	; float c[8]

  ; add a + b
  movsd xmm2, xmm0
  addsd xmm2, xmm1
  movsd real8 ptr [eax], xmm2

  ; sub a - b
  movsd xmm2, xmm0
  subsd xmm2, xmm1
  movsd real8 ptr [eax + 8], xmm2

  ; mul a * b
  movsd xmm2, xmm0
  mulsd xmm2, xmm1
  movsd real8 ptr [eax + 16], xmm2

  ; div a / b
  movsd xmm2, xmm0
  divsd xmm2, xmm1
  movsd real8 ptr [eax + 24], xmm2

  ; min
  movsd xmm2, xmm0
  minsd xmm2, xmm1
  movsd real8 ptr [eax + 32], xmm2
  
  ; max
  movsd xmm2, xmm0
  maxsd xmm2, xmm1
  movsd real8 ptr [eax + 40], xmm2

  ; fabs abs(b)
  movsd xmm2, xmm1
  andpd xmm2, AbsMaskDouble
  movsd real8 ptr [eax + 48], xmm2

  ; sqrt sqrt(fabs(b))
  sqrtsd xmm2, xmm2
  movsd real8 ptr [eax + 56], xmm2

  pop ebp
  ret
sseMathDouble endp

end