.model flat, c

.const
xmmtest qword 8234567812345678h, 8234567812345678h

; extern "C" void avxFloatPointCompare(double a, double b, bool r[8]);
.code
avxFloatPointCompare proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 24]
  vmovsd xmm0, real8 ptr [ebp + 8]
  vmovsd xmm1, real8 ptr [ebp + 16]

  ; eq
  vcmpeqsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2				; xmm2[63] = 0
  test ecx, 1
  setnz byte ptr [eax]

  ; neq
  vcmpneqsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 1]

  ; LT - less than
  vcmpltsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 2]

  ; LE - less than or equal
  vcmplesd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 3]

  ; GT - greater than
  vcmpgtsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 4]

  ; GE - greater than or equal
  vcmpgesd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 5]

  ; ORDER CMP
  vcmpordsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 6]

  ; UNORDER CMP
  vcmpunordsd xmm2, xmm0, xmm1
  vmovmskpd ecx, xmm2
  test ecx, 1
  setnz byte ptr [eax + 7]

  pop ebp
  ret
avxFloatPointCompare endp
end