
; extern "C" bool CallConventionNonVolatile(const Int64 * a, const Int64 * b, Int32 n, Int64 * sum_a, Int64 * sum_b, Int64 * prod_a, Int64 * prod_b);
; using stack frame pointer and non-volatile register
; xmm6 - xmm15 are non-volatile

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
NUM_PUSHREG     = 4
STK_LOCAL1      = 32		;	8 bytes * 4
STK_LOCAL2      = 16		;	8 bytes * 4
STK_PAD         = ((NUM_PUSHREG AND 1) XOR 1) * 8
STK_TOTAL       = STK_LOCAL1 + STK_LOCAL2 + STK_PAD
RBP_RA          = NUM_PUSHREG * 8 + STK_LOCAL1 + STK_PAD

;  ret address		+72
;  old rbp			+64
;  old rbx			+56
;  old r12			+48
;  old r13			+40
;  STK_PAD			+32
;  STk_LOCAL1 D		+24
;  STk_LOCAL1 C		+16
;  STk_LOCAL1 B		+8
;  STk_LOCAL1 A   <- RBP
;  STk_LOCAL2 B     -8
;  STk_LOCAL2 A	    -16 (RSP)

CallConventionNonVolatile proc frame
  push rbp
  .pushreg rbp
  push rbx
  .pushreg rbx
  push r12
  .pushreg r12
  push r13
  .pushreg r13

  sub rsp, STK_TOTAL
  .allocstack STK_TOTAL

  lea rbp, [rsp + STK_LOCAL2]
  .setframe rbp, STK_LOCAL2
  .endprolog

  ; init
  test r8d, r8d
  jle Error
  xor rbx, rbx
  xor r10, r10
  xor r11, r11
  mov r12, 1
  mov r13, 1

@@:
  mov rax, [rcx + rbx]
  add r10, rax
  imul r12, rax
  mov rax, [rdx + rbx]
  add r11, rax
  imul r13, rax

  add rbx, 8
  dec r8d
  jnz @B

  ; save
  mov [r9], r10							; sum_a
  mov rax, [rbp + RBP_RA + 40]
  mov [rax], r11						; sum_b
  mov rax, [rbp + RBP_RA + 48]
  mov [rax], r12						; prod_a
  mov rax, [rbp + RBP_RA + 56]
  mov [rax], r13						; prod_b
  mov rax, 1

Done:
  lea rsp, [rbp + STK_LOCAL1 + STK_PAD]
  pop r13
  pop r12
  pop rbx
  pop rbp
  ret
Error:
  xor eax, eax
  jmp Done
CallConventionNonVolatile endp
end