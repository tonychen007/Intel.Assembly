.model flat, c

; extern "C" void avcPackedFloatPointCompare(const YmmVal* a, const YmmVal* b, YmmVal c[8]);

.code
avcPackedFloatPointCompare proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovapd ymm0, ymmword ptr [eax]
  vmovapd ymm1, ymmword ptr [ecx]

  ; eq
  vcmpeqpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx], ymm2

  ; neq
  vcmpneqpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 32], ymm2

  ; lt
  vcmpltpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 64], ymm2

  ; le
  vcmplepd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 96], ymm2

  ; gt
  vcmpgtpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 128], ymm2

  ; ge
  vcmpgepd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 160], ymm2

  ; ord
  vcmpordpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 192], ymm2

  ; uunord
  vcmpunordpd ymm2, ymm0, ymm1
  vmovapd ymmword ptr [edx + 224], ymm2

  vzeroupper
  pop ebp
  ret
avcPackedFloatPointCompare endp
end