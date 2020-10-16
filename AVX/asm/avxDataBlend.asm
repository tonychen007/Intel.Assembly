.model flat, c

; extern "C" void avxDataBlendFloat(YmmVal * dst, YmmVal * src1, YmmVal * src2, YmmVal * src3);

.code
avxDataBlendFloat proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 12]
  mov ecx, [ebp + 16]
  mov edx, [ebp + 20]
  vmovaps ymm1, ymmword ptr [eax]
  vmovaps ymm2, ymmword ptr [ecx]
  vmovaps ymm3, ymmword ptr [edx]

  vblendvps ymm0, ymm1, ymm2, ymm3
  mov eax, [ebp + 8]
  vmovaps ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataBlendFloat endp

; extern "C" void avxDataBlendByte(YmmVal * dst, YmmVal * src1, YmmVal * src2, YmmVal * src3);
avxDataBlendByte proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 12]
  mov ecx, [ebp + 16]
  mov edx, [ebp + 20]
  vmovaps ymm1, ymmword ptr [eax]
  vmovaps ymm2, ymmword ptr [ecx]
  vmovaps ymm3, ymmword ptr [edx]

  ; vpblendw, vplendd requires imm8 ops
  vpblendvb ymm0, ymm1, ymm2, ymm3
  mov eax, [ebp + 8]
  vmovaps ymmword ptr [eax], ymm0

  vzeroupper
  pop ebp
  ret
avxDataBlendByte endp

end