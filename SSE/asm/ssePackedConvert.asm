.model flat, c

; extern "C" void ssePackedConvert(XmmVal * dst, XmmVal * src, CvtPackedOps ops);
.code
ssePackedConvert proc
  push ebp
  mov ebp, esp

  ; init
  mov ecx, [ebp + 16]
  cmp ecx, CvtPackedOpsCount
  jae Done
  mov edi, [ebp + 8]
  mov esi, [ebp + 12]
  jmp [CvtPackedOpsTable + ecx * 4]

ECVTDQ2PS:
  movdqa xmm0, [esi]
  cvtdq2ps xmm1, xmm0
  movaps [edi], xmm1
  jmp Done

ECVTDQ2PD:
  movdqa xmm0, [esi]
  cvtdq2pd xmm1, xmm0
  movapd [edi], xmm1
  jmp Done

ECVTPS2DQ:
  movaps xmm0, [esi] 
  cvtps2dq xmm1, xmm0
  movdqa [edi], xmm1
  jmp Done

ECVTPD2DQ:
  movapd xmm0, [esi] 
  cvtpd2dq xmm1, xmm0
  movdqa [edi], xmm1
  jmp Done

ECVTPS2PD:
  movaps xmm0, [esi]
  cvtps2pd xmm1, xmm0
  movapd [edi], xmm1
  jmp Done

ECVTPD2PS:
  movapd xmm0, [esi]
  cvtpd2ps xmm1, xmm0
  movaps [edi], xmm1
  jmp Done

Done:
  pop ebp
  ret
  
align 4
CvtPackedOpsTable dword ECVTDQ2PS, ECVTDQ2PD, ECVTPS2DQ, ECVTPD2DQ, ECVTPS2PD, ECVTPD2PS
CvtPackedOpsCount equ ($ - CvtPackedOpsTable) / sizeof dword
ssePackedConvert endp
end