.model flat, c

; extern "C" int MmxConvert(MmxVal * dst, MmxVal * src);
; pack src and dst into dst, word to byte, 4 words to 8 bytes
.code
MmxConvert proc
  push ebp
  mov ebp, esp

  ; init
  mov esi, [ebp + 8]
  mov edi, [ebp + 12]
  mov edx, [ebp + 16]
  movq mm0, [esi]
  movq mm1, [edi]

  ; PACKSSWB, signed word to byte
  ; IF > 127(7F) or < -128(80), then byte is set to corresponding val
  movq mm2, mm0
  packsswb mm2, mm1
  movq [edx], mm2

  ; PACKUSWB, saturated word to byte
  movq mm2, mm0
  packuswb mm2, mm1
  movq [edx + 8], mm2

  pop ebp
  ret
MmxConvert endp
end