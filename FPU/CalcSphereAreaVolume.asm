.model flat, c

.const
Csa	 real8 3.0
Cv   real8 4.0

.code
; sa = 4 * pi * r * r
; v = 4 * pi * r * r * (r / 3)
CalcSphereAreaVolume proc
  push ebp
  mov ebp, esp

  ; check radius
  xor eax, eax
  fld real8 ptr [ebp + 8]
  fldz
  fcomip st(0), st(1)
  fstp st(0)
  jp Done
  ja Done
  
  ; sa
  fld real8 ptr [ebp + 8]
  fld st(0)
  fmul st(0), st(0)
  fldpi
  fmul Cv
  fmulp
  mov edx, [ebp + 16]
  fst real8 ptr [edx]

  ; v
  fmulp
  fdiv Csa
  mov edx, [ebp + 20]
  fstp real8 ptr [edx]

  mov eax, 1
Done:
  pop ebp
  ret
CalcSphereAreaVolume endp
  end