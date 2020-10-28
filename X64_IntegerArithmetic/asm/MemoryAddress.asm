.const
FibVals		dword 0,1,1,2,3,5,8,13
			dword 21,34,55,89,144,233,377,610,987,1597
FibValsNum	dword ($ - FibVals) / sizeof dword
public FibValsNum

.data
FibValsSum	dword ?
public FibValsSum

; extern "C" int MemoryAddress(int i, int* v1, int* v2, int* v3, int* v4);
.code
MemoryAddress proc
  cmp ecx, 0
  jl InvalidIndex
  cmp ecx, FibValsNum
  jge InvalidIndex

  movsxd rcx, ecx
  mov [rsp + 8], rcx

  ; base reg
  mov r11, offset FibVals
  shl rcx, 2					; rcx = i * 4
  add r11, rcx					; r11 = FibVals + i * 4
  mov eax, [r11]
  mov [rdx], eax				; save to v2

  ; base reg + index reg
  mov r11, offset FibVals
  mov rcx, [rsp + 8]
  shl rcx, 2
  mov eax, [r11 + rcx]
  mov [r8], eax

  ; base reg + index reg + scale
  mov r11, offset FibVals
  mov rcx, [rsp + 8]
  mov eax, [r11 + rcx * 4]
  mov [r9], eax

  ; base reg + index reg + scale + disp
  mov r11, offset FibVals - 4
  mov rcx, [rsp + 8]
  mov eax, [r11 + rcx * 4 + 4]
  mov r10, [rsp + 40]
  mov [r10], eax

  ; final
  add FibValsSum, eax
  mov eax, 1
  ret

InvalidIndex:
  xor eax, eax
  ret
MemoryAddress endp
end