.model flat, c

; Float point format:
; 31    30 - 23      22 - 0
; Sign   Exp.Bais   Fraction
; so 01111111 11111111 11111111 = 0x7FFFFFFF;
.const
align 16
AbsMaskFloat	dword 7fffffffh, 7fffffffh, 7fffffffh, 7fffffffh
				dword 7fffffffh, 7fffffffh, 7fffffffh, 7fffffffh

NegMaskFloat    dword 80000000h, 80000000h, 80000000h, 80000000h
				dword 80000000h, 80000000h, 80000000h, 80000000h

; extern "C" void avxPackedFloatPointFloat(const YmmVal * a, const YmmVal * b, YmmVal c[6]);
; extern "C" void avxPackedFloatPointDouble(const YmmVal * a, const YmmVal * b, YmmVal c[5]);

.code
avxPackedFloatPointFloat proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovaps ymm0, ymmword ptr [eax]
  vmovaps ymm1, ymmword ptr [ecx]

  ; add
  vaddps ymm2, ymm0, ymm1
  vmovaps ymmword ptr [edx], ymm2

  ; sub
  vsubps ymm3, ymm0, ymm1
  vmovaps ymmword ptr [edx + 32], ymm3

  ; mul
  vmulps ymm4, ymm0, ymm1
  vmovaps ymmword ptr [edx + 64], ymm4

  ; div
  vdivps ymm5, ymm0, ymm1
  vmovaps ymmword ptr [edx + 96], ymm5

  ; abs
  ; vmovups - mov unalign ymmword
  vmovups ymm6, ymmword ptr [AbsMaskFloat]
  vandps ymm7, ymm0, ymm6
  vmovaps ymmword ptr [edx + 128], ymm7

  ; neg
  vxorps ymm7, ymm0, ymmword ptr [NegMaskFloat]
  vmovaps ymmword ptr [edx + 160], ymm7

  vzeroupper
  pop ebp
  ret
avxPackedFloatPointFloat endp

avxPackedFloatPointDouble proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  vmovaps ymm0, ymmword ptr [eax]
  vmovaps ymm1, ymmword ptr [ecx]

  ; min
  vminpd ymm2, ymm0, ymm1  

  ; max
  vmaxpd ymm3, ymm0, ymm1

  ; sqrt a
  vsqrtpd ymm4, ymm0

  ; horizontal add
  vhaddpd ymm5, ymm0, ymm1

  ; horizontal sub
  vhsubpd ymm6, ymm0, ymm1
  
  vmovapd ymmword ptr [edx], ymm2
  vmovapd ymmword ptr [edx + 32], ymm3
  vmovapd ymmword ptr [edx + 64], ymm4
  vmovapd ymmword ptr [edx + 96], ymm5
  vmovapd ymmword ptr [edx + 128], ymm6
  
  vzeroupper
  pop ebp
  ret
avxPackedFloatPointDouble endp

end