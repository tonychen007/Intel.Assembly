.model flat, c

; extern "C" void avxPackedInteger16(const YmmVal * a, const YmmVal * b, YmmVal c[6]);
; extern "C" void avxPackedInteger32(const YmmVal * a, const YmmVal * b, YmmVal c[5]);

.code
avxPackedInteger16 proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ecx]

  ; vpaddw
  vpaddw ymm2, ymm0, ymm1

  ; vpaddsw			;signed saturation
  vpaddsw ymm3, ymm0, ymm1

  ; vpsubw
  vpsubw ymm4, ymm0, ymm1

  ; vpsubsw
  vpsubsw ymm5, ymm0, ymm1

  ; vpminsw
  vpminsw ymm6, ymm0, ymm1

  ; vpmaxsw
  vpmaxsw ymm7, ymm0, ymm1

  vmovdqa ymmword ptr [edx], ymm2
  vmovdqa ymmword ptr [edx + 32], ymm3
  vmovdqa ymmword ptr [edx + 64], ymm4
  vmovdqa ymmword ptr [edx + 96], ymm5
  vmovdqa ymmword ptr [edx + 128], ymm6
  vmovdqa ymmword ptr [edx + 160], ymm7

  vzeroupper
  pop ebp
  ret
avxPackedInteger16 endp

avxPackedInteger32 proc
  push	ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ecx]

  vphaddd ymm2, ymm0, ymm1
  vphsubd ymm3, ymm0, ymm1
  vpmulld ymm4, ymm0, ymm1
  vpsllvd ymm5, ymm0, ymm1
  vpsravd ymm6, ymm0, ymm1

  vmovdqa ymmword ptr [edx], ymm2
  vmovdqa ymmword ptr [edx + 32], ymm3
  vmovdqa ymmword ptr [edx + 64], ymm4
  vmovdqa ymmword ptr [edx + 96], ymm5
  vmovdqa ymmword ptr [edx + 128], ymm6

  vzeroupper
  pop ebp
  ret
avxPackedInteger32 endp

end