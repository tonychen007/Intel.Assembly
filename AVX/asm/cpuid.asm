.model flat, c

CpuidRegs struct
RegEax	dword ?
RegEbx	dword ?
RegEcx	dword ?
RegEdx	dword ?
CpuidRegs ends

; extern "C" void avxCpuId(Uint32 eax, Uint32 ecx, CpuidRegs * out);
.code
avxCpuId proc
  push ebp
  mov ebp, esp
  push ebx
  push esi

  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  cpuid

  mov esi, [ebp + 16]
  mov [esi + CpuidRegs.RegEax], eax
  mov [esi + CpuidRegs.RegEbx], ebx
  mov [esi + CpuidRegs.RegEcx], ecx
  mov [esi + CpuidRegs.RegEdx], edx

  pop esi
  pop ebx
  pop ebp
  ret
avxCpuId endp

; extern "C" void avxXgetbv(Uint32 ecx, Uint32* eax, Uint32* edx);
avxXgetbv proc
  push ebp
  mov ebp, esp

  mov ecx, [ebp + 8]
  xgetbv
  mov ecx, [ebp + 12]
  mov [ecx], eax
  mov ecx, [ebp + 16]
  mov [ecx], edx

  pop ebp
  ret
avxXgetbv endp
end