.model flat, c

.code
; extern "C" int sseGetMxscr();
sseGetMxcsr proc
  push ebp
  mov ebp, esp
  sub esp, 4

  stmxcsr [ebp - 4]
  mov eax, [ebp - 4]

  mov esp, ebp
  pop ebp
  ret
sseGetMxcsr endp

; extern "C" int sseSetMxscr(int v);
sseSetMxcsr proc
  push ebp
  mov ebp, esp
  sub esp, 4

  ; mxscr is 16-bit
  mov eax, [ebp + 8]
  and eax, 0ffffh
  mov [ebp - 4], eax
  ldmxcsr [ebp - 4]

  mov esp, ebp
  pop ebp
  ret
sseSetMxcsr endp

; extern "C" SseRoundMode sseGetMxscrRM();
; bit 13 - 14 is for rounding mode

MxscrRcMask equ 9fffh  ; 1001 1111 1111 1111, rounding mode is bit 13-14, so mask out rounding mode
MxscrRcShift equ 13
sseGetMxcsrRM proc
  push ebp
  mov ebp, esp
  sub esp, 4
  
  stmxcsr [ebp - 4]
  mov eax, [ebp - 4]
  shr eax, MxscrRcShift
  and eax, 11b

  mov esp, ebp
  pop ebp
  ret
sseGetMxcsrRM endp

; extern "C" void sseSetMxscrRM(SseRoundMode rm);
; bit 13 - 14 is for rounding mode
sseSetMxcsrRM proc
  push ebp
  mov ebp, esp
  sub esp, 4

  mov ecx, [ebp + 8]
  and ecx, 11b
  shl ecx, MxscrRcShift    
  stmxcsr [ebp - 4]
  mov eax, [ebp - 4]
  and eax, MxscrRcMask   ; 1001 1111 1111 1111, mask out rounding mode
  or eax, ecx
  mov [ebp - 4], eax
  ldmxcsr [ebp - 4]

  mov esp, ebp
  pop ebp
  ret
sseSetMxcsrRM endp

; extern "C" void sseScalarConvert(XmmScalar * dst, XmmScalar * src, CvtOps ops);
sseScalarConvert proc
  push ebp
  mov ebp, esp

  ; load params
  mov ecx, [ebp + 16]
  mov esi, [ebp + 12]
  mov edi, [ebp + 8]
  cmp ecx, CvtOpsCount
  jae Done
  jmp [CvtOpsTable + ecx * 4]

ECVTSI2SS:
  mov eax, [esi]
  cvtsi2ss xmm0, eax
  movss real4 ptr [edi], xmm0
  mov eax, 1
  pop ebp
  ret
ECVTSS2SI:
  movss xmm0, real4 ptr [esi]
  cvtss2si eax, xmm0
  mov [edi], eax
  mov eax, 1
  pop ebp
  ret
ECVTSI2SD:
  mov eax, [esi]
  cvtsi2sd xmm0, eax
  movsd real8 ptr [edi], xmm0
  mov eax, 1
  mov esp, ebp
  pop ebp
  ret
ECVTSD2SI:
  movsd xmm0, real8 ptr [esi]
  cvtsd2si eax, xmm0
  mov [edi], eax
  mov eax, 1
  pop ebp
  ret
ECVTSS2SD:
  movss xmm0, real4 ptr [esi]
  cvtss2sd xmm1, xmm0
  movsd real8 ptr [edi], xmm1
  mov eax, 1
  pop ebp
  ret
ECVTSD2SS:
  movsd xmm0, real8 ptr [esi]
  cvtsd2ss xmm1, xmm0
  movss real4 ptr [edi], xmm1
  mov eax, 1
  pop ebp
  ret
Done:
  xor eax, eax
  pop ebp
  ret

align 4
CvtOpsTable dword ECVTSI2SS, ECVTSS2SI, ECVTSI2SD, ECVTSD2SI, ECVTSS2SD, ECVTSD2SS
CvtOpsCount equ ($ - CvtOpsTable) / sizeof dword
sseScalarConvert endp

end