.model flat, c

.const
iReal4_Min	dword 0FF7FFFFFh
iReal4_Max	dword  7F7FFFFFh

.code
MinAndMax proc
  push ebp
  mov ebp, esp

  ; check size
  xor eax,eax
  mov edx, [ebp + 8]
  mov ecx, [ebp + 12]
  test ecx, ecx
  jle Done

  fld iReal4_Min			; actual max value
  fld iReal4_Max			; actual min value

  ;	Min		st3
  ;	Max		st2
  ; Val		st1
  ; Val		st0
@@:
  fld real4 ptr [edx]
  fld st(0)
  fcomi st(0), st(2)			; st2 < st0, mv st2 -> st0
  fcmovnb st(0), st(2)
  fstp st(2)					; min value		

  fcomi st(0), st(2)
  fcmovb st(0), st(2)		; st2 > st0, mv st2 -> st0
  fstp st(2)					; max value

  add edx, 4
  dec ecx
  jnz @B
Done:
  mov eax, [ebp + 16]
  fstp real4 ptr [eax]
  mov eax, [ebp + 20]
  fstp real4 ptr [eax]	
  pop ebp
  ret
MinAndMax endp
  end