include <autoMacro.inc>

; extern "C" void CallConventionAutomate(float * a, float * b, float * sum, float * prod);
.code
CallConventionAutomate proc frame
  _CreateFrame Cc4, 16, 48, rbx, r12, r13
  _SaveXmmRegs xmm0,xmm1, xmm2
  _EndProlog
  
  ; demo
  mov qword ptr [rbp+Cc4OffsetHomeRCX],rcx
  mov qword ptr [rbp+Cc4OffsetHomeRDX],rdx
  mov qword ptr [rbp+Cc4OffsetHomeR8],r8
  mov qword ptr [rbp+Cc4OffsetHomeR9],r9

  movss xmm0, real4 ptr [rcx]
  movss xmm1, real4 ptr [rdx]
  movss xmm2, xmm0
  addss  xmm0, xmm1
  mulss  xmm2, xmm1
  movss real4 ptr [r8], xmm0
  movss real4 ptr [r9], xmm2

  _RestoreXmmRegs xmm0,xmm1, xmm2
  _DeleteFrame rbx, r12, r13

  ret
CallConventionAutomate endp
end