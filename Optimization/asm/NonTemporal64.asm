IFDEF ASMX86_64

.code

_calcResult64 macro MovInstr

  ; check args
  test rcx, 0fh
  jnz Error
  test rdx, 0fh
  jnz Error
  test r8, 0fh
  jnz Error

  test r9d, r9d
  jle Error
  test r9d, 3
  jnz Error

  ; calc sqrt a,b,c
  xor eax, eax
  align 16

@@:
  movaps xmm0, xmmword ptr [rdx + rax]
  movaps xmm1, xmmword ptr [r8 + rax]
  mulps xmm0, xmm0
  mulps xmm1, xmm1
  addps xmm0, xmm1
  sqrtps xmm0, xmm0
  MovInstr xmmword ptr [rcx + rax], xmm0

  add rax, 16	; xmm 16 byte
  sub r9d, 4
  jnz @B

  mov rax, 1
  ret

Error:
  xor eax, eax
  ret
endm

; extern void CalcResultMovaps(float* c, const float* a, const float* b, int n);
; extern void CalcResultMovntps(float* c, const float* a, const float* b, int n);

CalcResultMovaps proc
  _calcResult64 movaps
CalcResultMovaps endp

CalcResultMovntps proc
  _calcResult64 movntps
CalcResultMovntps endp
ENDIF

end