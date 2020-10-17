.model flat, c

; extern "C" Uint64 avxFlagLessMul(Uint32 a, Uint32 b, Uint8 flag[2]);

.code
avxFlagLessMul proc
  push ebp
  mov ebp, esp

  ; init
  mov ecx, [ebp + 16]
  ; Load Status Flags into AH Register
  lahf
  mov byte ptr [ecx], ah

  ; mulx op1,op2,op3 
  ; mul op1 * op3, save low half in op2, and high half in op1
  mov edx, [ebp + 12]
  mulx edx, eax, [ebp + 8]

  push eax
  lahf
  mov byte ptr [ecx + 1], ah
  pop eax

  pop ebp
  ret
avxFlagLessMul endp

; extern "C" void avxFlagLessShift(Int32 x, Uint32 count, Int32 ret[3]);
avxFlagLessShift proc
  push ebp
  mov ebp, esp

  ; init
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]

  sarx eax, [ebp + 8], ecx
  mov [edx], eax
  shlx eax, [ebp + 8], ecx
  mov [edx + 4], eax
  shrx eax, [ebp + 8], ecx
  mov [edx + 8], eax

  pop ebp
  ret
avxFlagLessShift endp

end