.model flat, c

; extern "C" void sseDotUnpack(XmmVal * dst, XmmVal * src, DotUnpack ops);
.code
sseDotUnpack proc
  push ebp
  mov ebp, esp

  ; init
  mov ecx, [ebp + 16]
  cmp ecx, DotUnpackMovOpsCount
  jae Done
  mov edi, [ebp + 8]
  mov esi, [ebp + 12]
  jmp [DotUnpackMovOpsTable + ecx * 4]

EDOTFP:
  ; dst = src * dst, all eles and store
  movaps xmm0, [esi]
  movaps xmm1, [edi]
  
  ; 1011 is conditional mask, which eles should be multiplied
  ; 0010b is broadcast mask, 1 is store the value in dest, 0 is discard
  dpps xmm0, xmm1, 10110011b
  movaps [edi], xmm0
  jmp Done

EUNPACKFP:
  movaps xmm0, [esi]
  movaps xmm1, [edi]
  unpcklps xmm0, xmm1
  movaps [edi], xmm0
  jmp Done

EMOVLHPS:
  movaps xmm0, [esi]
  movaps xmm1, [edi]
  movlhps xmm0, xmm1				; mov low quadword of xmm1 to high quadword of xmm0
  ; movlps xmm0, qword ptr [edi]
  movaps [edi], xmm0
  jmp Done

EINSERTFP:
  movaps xmm0, [esi]
  movaps xmm1, [edi]

  ; src to copy [6:7]
  ; dst to overwrtitten [4:5]
  ; zero to set [0:3]
  insertps xmm1, xmm0, 10110101b
  movaps [edi], xmm1
  jmp Done

EDOTDP:
  ; dst = src * dst, all eles and store
  movapd xmm0, [esi]
  movapd xmm1, [edi]
  
  ; [5:4] is conditional mask, which eles should be multiplied
  ; [0:1] is broadcast mask, 1 is store the value in dest, 0 is discard
  dppd xmm0, xmm1, 00110001b
  movapd [edi], xmm0
  jmp Done

EUNPACKDP:
  movapd xmm0, [esi]
  movapd xmm1, [edi]
  unpckhpd xmm0, xmm1
  movapd [edi], xmm0
  jmp Done

EMOVHPD:
  movapd xmm0, [esi]
  movapd xmm1, [edi]
  movhpd xmm0, qword ptr [edi + 8]		; mov mm64 [edi] to high quadword of xmm0 
  movapd [edi], xmm0
  jmp Done

Done:
  pop ebp
  ret

align 4
DotUnpackMovOpsTable dword EDOTFP, EUNPACKFP, EMOVLHPS, EINSERTFP, EDOTDP, EUNPACKDP, EMOVHPD
DotUnpackMovOpsCount equ ($ - DotUnpackMovOpsTable) / sizeof dword
sseDotUnpack endp
end