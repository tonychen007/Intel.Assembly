.model flat, c

.const
FToCconst	real8	0.5555556
CtoFConst	real8	1.8
i32			dword	32

;	F = C * 9 / 5 + 32
;	C = (F - 32) * 5 / 9
.code
CtoF proc
  push ebp
  mov ebp, esp

  fld real8 ptr [ebp + 8]
  fmul CToFconst
  fiadd i32

  pop ebp
  ret
CtoF endp

FtoC proc
  push ebp
  mov ebp, esp

  fld FToCconst
  fld real8 ptr [ebp + 8]
  fild i32
  fsubp
  fmulp

  pop ebp
  ret
FtoC endp
  end