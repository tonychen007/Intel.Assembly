; extern "C" Int64 CallConvention(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);

.code
CallConvention proc frame
  push rbp
  .pushreg rbp

  sub rsp, 16
  .allocstack 16

  mov rbp, rsp
  .setframe rbp, 0

  ;  ret address    24
  ;  old ebp        16
  ;  local var1     8
  ;  local var2     0    [rbp, rsp]
RBP_RA = 24
  .endprolog

  ; a + b + c + d
  movsx rcx, cl
  movsx rdx, dx
  movsxd r8, r8d
  add rcx, rdx
  add r8, r9
  add rcx, r8
  mov [rbp], rcx

  ; e + f + g + h
  movsx rcx, byte ptr [rbp + RBP_RA + 40]
  movsx rdx, word ptr [rbp + RBP_RA + 48]
  movsxd r8, dword ptr [rbp + RBP_RA + 56]
  add rcx, rdx
  add r8, qword ptr [rbp + RBP_RA + 64]
  add rcx, r8

  ; final
  mov rax, [rbp]
  add rax, rcx

  add rsp, 16
  pop rbp
  ret
CallConvention endp
end