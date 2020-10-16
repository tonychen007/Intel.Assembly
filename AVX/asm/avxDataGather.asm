.model flat, c

; extern "C" void avxDataGatherFloat(YmmVal * dst, YmmVal * index, YmmVal * mask, float* f);

.code
avxDataGatherFloat proc
  push ebp
  mov ebp, esp
  push ebx

  ; init
  mov eax, [ebp + 8]
  mov ebx, [ebp + 12]
  mov ecx, [ebp + 16]
  mov edx, [ebp + 20]
  vmovaps ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ebx]	; index scale
  vmovdqa ymm2, ymmword ptr [ecx]

  ; The memory operand uses the VSIB form of the SIB byte to specify a general purpose register 
  ; operand as the common base, a vector register for an array of indices relative to the base 
  ; and a constant scale factor

  ; In VSIB memory addressing, the SIB byte consists of:
  ; The scale field (bit 7:6) specifies the scale factor.
  ; The index field (bits 5:3) specifies the register number of the vector index register, each element in the vector
  ; register specifies an index.
  ; The base field (bits 2:0) specifies the register number of the base register.

  vgatherdps ymm0, [edx + ymm1*4], ymm2
  vmovaps ymmword ptr [eax], ymm0
  vmovdqa ymmword ptr [ebx], ymm1
  vmovdqa ymmword ptr [ecx], ymm2

  vzeroupper
  pop ebx
  pop ebp
  ret
avxDataGatherFloat endp

; extern "C" void avxDataGatherInt64(YmmVal * dst, YmmVal * index, YmmVal * mask, Int64* f);
avxDataGatherInt64 proc
  push ebp
  mov ebp, esp
  push ebx

  ; init
  mov eax, [ebp + 8]
  mov ebx, [ebp + 12]
  mov ecx, [ebp + 16]
  mov edx, [ebp + 20]
  vmovdqa ymm0, ymmword ptr [eax]
  vmovdqa ymm1, ymmword ptr [ebx]	; index scale
  vmovdqa ymm2, ymmword ptr [ecx]

  vpgatherdq ymm0, [edx + xmm1*8], ymm2
  vmovdqa ymmword ptr [eax], ymm0
  vmovdqa ymmword ptr [ebx], ymm1
  vmovdqa ymmword ptr [ecx], ymm2

  vzeroupper
  pop ebx
  pop ebp
  ret
avxDataGatherInt64 endp
end