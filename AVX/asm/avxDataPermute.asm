.model flat, c

; extern "C" void avxDataPermuteInt(YmmVal * dst, YmmVal * src, YmmVal * ind);
.code
avxDataPermuteInt proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm1, ymmword ptr [edx]

  ; vpermd dst, ind, src
  vpermd ymm0, ymm1, ymmword ptr [ecx]
  vmovdqa ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataPermuteInt endp

; extern "C" void avxDataPermuteFloat(YmmVal * dst, YmmVal * src, YmmVal * ind);
avxDataPermuteFloat proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm1, ymmword ptr [edx]

  ; vpermps dst, ind, src
  vpermps ymm0, ymm1, ymmword ptr [ecx]
  vmovdqa ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataPermuteFloat endp

; extern "C" void avxDataPermuteFloatInLane(YmmVal * dst, YmmVal * src, YmmVal * ind);
avxDataPermuteFloatInLane proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovdqa ymm1, ymmword ptr [ecx]

  ; vpermilps dst, src, ind
  vpermilps ymm0, ymm1, ymmword ptr [edx]
  vmovdqa ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataPermuteFloatInLane endp

end