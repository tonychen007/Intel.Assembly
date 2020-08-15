.model flat, c

.code
CalcMeanStdev proc
  push ebp
  mov ebp, esp
  sub esp, 4

  xor eax, eax
  mov ecx, [ebp + 12]
  cmp ecx, 1
  jle Done
  dec ecx
  mov [ebp - 4], ecx		; stdev sample is small, so div / (n - 1)
  inc ecx
  mov edx, [ebp + 8]		; arr
  fldz					; sum = 0.0

@@:
  fadd real8 ptr [edx]
  add edx, 8
  dec ecx
  jnz @B
  fidiv dword ptr [ebp + 12]
  mov eax, [ebp + 16]
  fstp real8 ptr [eax]
  fstp st(0)

  mov edx, [ebp + 8]
  mov ecx, [ebp + 12]
  mov eax, [ebp + 16]
  fld real8 ptr [eax]
  fldz

@@:
  fld real8 ptr [edx]
  fsub st(0), st(2)
  fmul st(0), st(0)
  faddp
  add edx, 8
  dec ecx
  jnz @B
  fidiv dword ptr [ebp - 4]
  fsqrt
  mov eax, [ebp + 20]
  fstp real8 ptr [eax]
  fstp st(0)

Done:
  mov esp, ebp
  pop ebp
  ret
CalcMeanStdev endp
  end