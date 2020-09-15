.model flat, c

.const
align 16
PxorNotMask db 16 dup(0ffh)

; extern "C" int sseStringReplace(const char* str, const char oldChar, const char newChar);
; need to consider char* without 4096, within 4080 - 4096, and acroos 4080 - next page
; because xmm is 16 bytes
.code
sseStringReplace proc
  push ebp
  mov ebp, esp
  push ebx
  push esi
  push edi

  ; init
  mov eax, [ebp + 8]
  sub eax, 16
  xor edi, edi

  ; old char and new char
  movzx ecx, byte ptr [ebp + 12]
  movd xmm1, ecx							; oldchar
  movzx ecx, byte ptr [ebp + 16]
  movd xmm6, ecx							; newchar
  pxor xmm5, xmm5
  pshufb xmm6, xmm5							; rewritten xmm6, xmm5 is bit-order
  movdqa xmm7, xmmword ptr PxorNotMask

  ; check if within nearest page, page is 4k
Loop1:
  add eax, 16								; pcmpistri deals with 16 byte xmm operands
  mov edx, eax
  and edx, 0fffh							; 4095 mask of 4096
  cmp edx, 0ff0h							; ff0 = 4080 + 16 = 4096
  ja WithinNearPage

  ; compare current
  movdqu xmm2, [eax]						; xmm2, current string

  ; [3:2] - 00, match any char in range (oldchar). [4] - 00, Positive IntRes2 = IntRes1
  ; [6] - 0 pcmpistrm IntRes2 saved as byte/word in xmm0
  pcmpistrm xmm1, xmm2, 01000000b			; 40h, if matched, CF is set. Mask is saved in xmm1.
											; 00 not matched, FF matched.
  setz cl									; If '\0' is found, ZF is set.
  jc MatchFound
  jz Done
  jmp Loop1

MatchFound:
  ; most significant bit of each byte in xmm1 to edx
  ; xmm0 is FF FF FF FF FF FF FF
  ; binary of FF is 1111 1111, so the MSB of xmm0 is 1 1 1 1 1 1 1
  ; so, edx is 0111 1111 = 7F
  pmovmskb edx, xmm0
  popcnt edx, edx
  add edi, edx

  ; Replace
  movdqa xmm3, xmm0							; xmm0 is match mask
  pxor xmm0, xmm7							; xmm7 is PxorNotMask, old char set to 00, others set to FF
  pand xmm0, xmm2							; remove old chars, xmm0 is now chars without oldchars
  pand xmm3, xmm6
  pxor xmm0, xmm3
  movdqu [eax], xmm0
  or cl, cl
  jnz Done									; '\0' is not found
  jmp Loop1

WithinNearPage:
  mov ecx, 4096
  sub ecx, edx
  mov dl, [ebp + 12]
  mov dh, [ebp + 16]

Loop2:
  mov bl, [eax]
  or bl, bl
  jz Done
  cmp dl, bl
  jne @F
  mov [eax], dh
  inc edi
@@:
  inc eax
  dec ecx
  jnz Loop2

  ; remaing text in the next 4096 block
  sub eax, 16
Loop3:
  add eax, 16
  movdqa xmm2, [eax]
  pcmpistrm xmm1, xmm2, 01000000b
  setz cl
  jc MatchFound2
  jz Done
  jmp Loop3

MatchFound2:
  pmovmskb edx, xmm0
  popcnt edx, edx
  add edi, edx

  ; Replace
  movdqa xmm3, xmm0							; xmm0 is match mask
  pxor xmm0, xmm7							; xmm7 is PxorNotMask, old char set to 00, others set to FF
  pand xmm0, xmm2							; remove old chars, xmm0 is now chars without oldchars
  pand xmm3, xmm6
  pxor xmm0, xmm3
  movdqu [eax], xmm0
  or cl, cl
  jnz Done									; '\0' is not found
  jmp Loop3

Done:
  mov eax, edi
  pop edi
  pop esi
  pop ebx
  pop ebp
  ret
sseStringReplace endp
end