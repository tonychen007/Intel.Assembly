.model flat, c

.const
Deg2Rad real8 0.0174532952
one80 dword 180

.code
SinCos proc
  push ebp
  mov ebp, esp

  fld real4 ptr [ebp + 8]
  fldpi
  fild one80
  fdivp st(1), st(0)
  fmulp st(1), st(0)
  fsincos	; cos st(0), sin st(1)

  mov eax, [ebp + 12]
  fstp real4 ptr [eax]
  mov eax, [ebp + 16]
  fstp real4 ptr [eax]
  pop ebp
  ret
SinCos endp
  end