.model flat, c

; copy from ymm to ymm
; extern "C" void avxDataBroadcastInt(YmmVal * dst, const XmmVal * src, Brop op);
.code
avxDataBroadcastInt proc
  push ebp
  mov ebp, esp
  
  ; init
  mov eax, [ebp + 16]
  cmp eax, BropTableCount
  jae Done
  mov ecx, [ebp + 8]	; dst
  mov edx, [ebp + 12]	; src
  vmovdqa xmm0, xmmword ptr [edx]
  mov edx, [BropTable + 4*eax]
  jmp edx

BropByte:
  vpbroadcastb ymm1, xmm0
  vmovdqa ymmword ptr [ecx], ymm1
  vzeroupper
  pop ebp
  ret
BropWord:
  vpbroadcastw ymm1, xmm0
  vmovdqa ymmword ptr [ecx], ymm1
  vzeroupper
  pop ebp
  ret
BropDword:
  vpbroadcastd ymm1, xmm0
  vmovdqa ymmword ptr [ecx], ymm1
  vzeroupper
  pop ebp
  ret
BropQword:
  vpbroadcastq ymm1, xmm0
  vmovdqa ymmword ptr [ecx], ymm1
  vzeroupper
  pop ebp
  ret

Done:
  pop ebp
  ret

align 4
BropTable dword BropByte, BropWord, BropDword, BropQword
BropTableCount equ ($ - BropTable) / sizeof dword

avxDataBroadcastInt endp

; extern "C" void avxDataBroadcastFloat(YmmVal * dst, float val);
avxDataBroadcastFloat proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  vbroadcastss ymm0, real4 ptr [ebp + 12]
  vmovaps ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataBroadcastFloat endp

; extern "C" void avxDataBroadcastDouble(YmmVal * dst, double val);
avxDataBroadcastDouble proc
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  vbroadcastsd ymm0, real8 ptr [ebp + 12]
  vmovaps ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataBroadcastDouble endp
end