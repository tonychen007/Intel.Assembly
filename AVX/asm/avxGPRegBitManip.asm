.model flat, c

; extern "C" void avxGprCountZeroBits(Uint32 x, Uint32 * lzcnt, Uint32 * tzcnt);
.code
avxGprCountZeroBits proc
  push ebp
  mov ebp, esp

  ; init
  mov eax, [ebp + 8]
  mov esi, [ebp + 12]
  mov edi, [ebp + 16]
  lzcnt ecx, eax
  mov [esi], ecx
  tzcnt ecx, eax
  mov [edi], ecx

  pop ebp
  ret
avxGprCountZeroBits endp

; extern "C" Uint32 avxGprBextr(Uint32 x, Uint8 st, Uint8 len);
avxGprBextr proc
  push ebp
  mov ebp, esp

  ; init 
  mov cl, [ebp + 12]
  mov ch, [ebp + 16]
  bextr eax, [ebp + 8], ecx

  pop ebp
  ret
avxGprBextr endp

; extern "C" Uint32 avxGprAndNot(Uint32 x, Uint32 y);
; and of (~y) and save in x

avxGprAndNot proc
  push ebp
  mov ebp, esp

  ; init
  mov ecx, [ebp + 12]
  andn eax, ecx, [ebp + 8]

  pop ebp
  ret
avxGprAndNot endp

end
