
; extern "C" void CallConventionNonVolatileXMM(double* a, double* b, double * sum, double * prod);

.code
; Named expressions for constant values.
;
; NUM_PUSHREG   = number of prolog non-volatile register pushes
; STK_LOCAL1    = size in bytes of STK_LOCAL1 area (see figure in text)
; STK_LOCAL2    = size in bytes of STK_LOCAL2 area (see figure in text)
; STK_PAD       = extra bytes (0 or 8) needed to 16-byte align RSP
; STK_TOTAL     = total size in bytes of local stack
; RBP_RA        = number of bytes between RBP and ret addr on stack

; In X64, rsp must be align to 16 byte
; call push ret address, and must sub 8 byte
NUM_PUSHREG     = 2
STK_LOCAL1      = 32		;	16 xmm bytes * 2
STK_LOCAL2      = 32		;	16 xmm bytes * 2
STK_PAD         = ((NUM_PUSHREG AND 1) XOR 1) * 8
STK_TOTAL       = STK_LOCAL1 + STK_LOCAL2 + STK_PAD
RBP_RA          = NUM_PUSHREG * 8 + STK_LOCAL1 + STK_PAD


CallConventionNonVolatileXMM proc frame
  push rbp
  .pushreg rbp
  push rbx
  .pushreg rbx

  sub rsp, STK_TOTAL
  .allocstack STK_TOTAL

  lea rbp, [rsp + STK_LOCAL2]
  .setframe rbp, STK_LOCAL2

  ; saves xmm on the stack
  movdqa [rbp - STK_LOCAL2], xmm12
  .savexmm128 xmm12, 0
  movdqa [rbp - STK_LOCAL2 + 16], xmm13
  .savexmm128 xmm13, 16
  .endprolog

  ; init
  movsd xmm12, real8 ptr [rcx]
  movsd xmm13, real8 ptr [rdx]
  addsd xmm12, xmm13
  mulsd xmm13, real8 ptr [rcx]
  movsd real8 ptr [r8], xmm12
  movsd real8 ptr [r9], xmm13

  ; restore xmm and esp
  movdqa xmm12, [rbp - STK_LOCAL2]
  movdqa xmm13, [rbp - STK_LOCAL2 + 16]
  lea rsp, [rbp + STK_LOCAL1 + STK_PAD]
  pop rbx
  pop rbp
  ret
CallConventionNonVolatileXMM endp
end