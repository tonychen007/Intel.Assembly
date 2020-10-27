; extern "C" Int64 IntegerAdd(Int64 a, Int64 b, Int64 c, Int64 d, Int64 e, Int64 f);
; the first four int for pointer arg are passed by rcx, rdx, r8 r9
; the remaining are passed by stack
.code
IntegerAdd proc
  add rcx, rdx			; rcx = a + b
  add r8, r9			; r8 = c + d

  mov rax, [rsp + 40]	; e
  add rax, [rsp + 48]	; rax = e + f

  add rcx, r8			; rcx = a + b + c + d
  add rax, rcx			; rax = a + b + c + d + e + f

  ret
IntegerAdd endp

; extern "C" Int64 IntegerMul(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);
IntegerMul proc
  movsx r10, cl
  movsx r11, dx
  imul r10, r11			; r10 = a * b

  movsxd rcx, r8d
  imul rcx, r9			; rcx = c * d

  movsx r8, byte ptr [rsp + 40]
  movsx r9, word ptr [rsp + 48]
  imul r8, r9			; r8 = e * f

  movsxd rax, dword ptr [rsp + 56]
  imul rax, [rsp + 64]	; rax = g * h

  ; final
  imul r10, rcx;
  imul rax, r8
  imul rax, r10

  ret
IntegerMul endp

; extern "C" Int64 IntegerDiv(Int64 a, Int64 b, Int64 quo_rem_ab[2], Int64 c, Int64 d, Int64 quo_rem_cd[2]);
IntegerDiv proc
  mov [rsp + 16], rdx			; b
  mov rax, rcx					; a
  cqo
  idiv qword ptr [rsp + 16]		; a / b
  mov [r8], rax
  mov [r8 + 8], rdx

  mov rax, r9					; c
  cqo
  idiv qword ptr [rsp + 40]		; c / d
  mov r10, [rsp + 48]
  mov [r10], rax
  mov [r10 + 8], rdx

  ret
IntegerDiv endp

end