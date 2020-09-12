.model flat, c

; extern "C" int sseStringCalcLength(const char* str);
.code
sseStringCalcLength proc
  push ebp
  mov ebp, esp

  ; init char range
  mov eax, [ebp + 8]
  sub eax, 16			; buff_size is 8192, str = buff + offset. Here is loop-carry, because @@ set eax += 16. loop-carry techs
  mov edx, 0ff01h		; char range
  movd xmm1, edx

  ; check if within nearest page, page is 4k
@@:
  add eax, 16			; pcmpistri deals with 16 byte xmm operands
  mov edx, eax
  and edx, 0fffh		; 4095 mask of 4096
  cmp edx, 0ff0h		; ff0 = 4080 + 16 = 4096
  ja WithinNearPage

  ; [3:2] - 01, match char in range (01-ff). [4] - 01, Negative IntRes1. if '\0' is met with, ZF will be set to 1
  pcmpistri xmm1, [eax], 00010100b
  jnz @B

  ; calc len, ecx is the index of '\0'
  ; cannot use 'mov eax, ecx' because [eax] may be longer than 16, says it is 18
  ; so, the ecx index bit is 2. We use eax + ecx - [ebp + 8]
 
  add eax, ecx
  sub eax, [ebp + 8]
  pop ebp
  ret

WithinNearPage:
  mov ecx, 4096
  sub ecx, edx			; remaining byte to 4096

  ; because there are fewer bytes than 16, so use loop
@@:
  mov dl, byte ptr [eax]
  or dl, dl
  jz Done
  inc eax
  loop @B

  ; remaining of text string in next memory 4K block, using 16-bytes block
  sub eax, 16
@@:
  add eax, 16
  pcmpistri xmm1, [eax], 00010100b
  jnz @B
  add eax, ecx

Done:
  sub eax, [ebp + 8]
  pop ebp
  ret
sseStringCalcLength endp

end