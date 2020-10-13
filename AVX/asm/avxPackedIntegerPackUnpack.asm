.model flat, c

; extern "C" void avxPiUnpackDWord2QuadWord(const YmmVal * a, const YmmVal * b, YmmVal c[2]);
; extern "C" void avxPiPackDWord2Word(const YmmVal * a, const YmmVal * b, YmmVal* c);

.code
avxPiUnpackDWord2QuadWord proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ecx]

  vpunpckldq ymm2, ymm0, ymm1	; low part of ymm0 and ymm1
  vpunpckhdq ymm3, ymm0, ymm1	; high part of ymm0 and ymm1

  vmovdqa ymmword ptr [edx], ymm2
  vmovdqa ymmword ptr [edx + 32], ymm3

  vzeroupper
  pop ebp
  ret
avxPiUnpackDWord2QuadWord endp

avxPiPackDWord2Word proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ecx]

  vpackssdw ymm2, ymm0, ymm1			; ss = signed situration
  vmovdqa ymmword ptr [edx], ymm2

  vzeroupper
  pop ebp
  ret
avxPiPackDWord2Word endp

end
