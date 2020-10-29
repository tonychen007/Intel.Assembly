ClVal struct
  a8		byte ?
  pad1		byte ?
  a16		word ?
  a32		dword ?
  a64		qword ?
  b8		byte ?
  pad2		byte ?
  b16		word ?
  b32		dword ?
  b64		qword ?
ClVal ends

; extern "C" void CalcLogical(ClVal * cl, Uint8 c8[3], Uint16 c16[3], Uint32 c32[3], Uint64 c64[3]);
.code
CalcLogical proc
  ; 8 bit
  mov r10b, [rcx + ClVal.a8]
  mov r11b, [rcx + ClVal.b8]

  mov al, r10b
  and al, r11b
  mov [rdx], al

  mov al, r10b
  or al, r11b
  mov [rdx + 1], al

  mov al, r10b
  xor al, r11b
  mov [rdx + 2], al

  ; 16 bit
  mov r10w, [rcx + ClVal.a16]
  mov r11w, [rcx + ClVal.b16]

  mov ax, r10w
  and ax, r11w
  mov [r8], ax

  mov ax, r10w
  or ax, r11w
  mov [r8 + 2], ax

  mov ax, r10w
  xor ax, r11w
  mov [r8 + 4], ax

  ; 32 bit
  mov r10d, [rcx + ClVal.a32]
  mov r11d, [rcx + ClVal.b32]

  mov eax, r10d
  and eax, r11d
  mov [r9], eax

  mov eax, r10d
  or eax, r11d
  mov [r9 + 4], eax

  mov eax, r10d
  xor eax, r11d
  mov [r9 + 8], eax

  ; 64 bit
  mov r8, [rsp + 40]
  mov r10, [rcx + ClVal.a64]
  mov r11, [rcx + ClVal.b64]

  mov rax, r10
  and rax, r11
  mov [r8], rax

  mov rax, r10
  or rax, r11
  mov [r8 + 8], rax

  mov rax, r10
  xor rax, r11
  mov [r8 + 16], rax

  ret
CalcLogical endp
end