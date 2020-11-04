IFDEF ASMX86_32
.model flat, c
.code

_calcResult32 macro MovInstr
  push ebp
  mov ebp, esp
  push ebx
  push edi

  ; check args
  mov edi, [ebp + 8]
  test edi, 0fh
  jnz Error
  mov ebx, [ebp + 12]
  test ebx, 0fh
  jnz Error
  mov edx, [ebp + 16]
  test edx, 0fh
  jnz Error

  mov ecx, [ebp + 20]
  test ecx, ecx
  jle Error
  test ecx, 3
  jnz Error

  ; calc sqrt a,b,c
  xor eax, eax
  align 16

@@:
  movaps xmm0, xmmword ptr [ebx + eax]
  movaps xmm1, xmmword ptr [edx + eax]
  mulps xmm0, xmm0
  mulps xmm1, xmm1
  addps xmm0, xmm1
  sqrtps xmm0, xmm0
  MovInstr xmmword ptr [edi + eax], xmm0

  add eax, 16	; xmm 16 byte
  sub ecx, 4
  jnz @B

  mov eax, 1
  pop edi
  pop ebx
  pop ebp
  ret

Error:
  xor eax, eax
  pop edi
  pop ebx
  pop ebp
  ret
endm

; extern void CalcResultMovaps(float* c, const float* a, const float* b, int n);
; extern void CalcResultMovntps(float* c, const float* a, const float* b, int n);

CalcResultMovaps proc
  _calcResult32 movaps
CalcResultMovaps endp

CalcResultMovntps proc
  _calcResult32 movntps
CalcResultMovntps endp
ENDIF

end