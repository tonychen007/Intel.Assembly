.model flat, c

; extern "C" int MmxCalcMean(const Uint8 * x, int n, Uint8* sum, double* mean);
; return:	-1 invalid num
;			 0 success

.code
extern NMIN:dword
extern NMAX:dword

MmxCalcMean proc
  push ebp
  mov ebp, esp
  sub esp, 8

  ; check n
  xor eax, eax
  mov ecx, [ebp + 12]
  cmp ecx, NMIN
  jle Error
  cmp ecx, NMAX
  jae Error
  test ecx, 0fh		; ecx % 16 != 0
  jnz Error
  shr ecx, 4		; 16 bytes chunk

  mov eax, [ebp + 8]
  pxor mm4, mm4
  pxor mm5, mm5
  pxor mm7, mm7

@@:
  movq mm0, [eax]
  movq mm1, [eax + 8]
  ; promot byte to word
  movq mm2, mm0
  movq mm3, mm1

  punpcklbw mm0, mm7	; pack byte to word in two mm
  punpcklbw mm1, mm7
  punpckhbw mm2, mm7
  punpckhbw mm3, mm7

  ; low bit of two val is in mm0, mm1
  ; high bit of two val is in mm2, mm3
  ; add them respectively
  paddw mm0, mm1
  paddw mm2, mm3
  paddw mm0, mm2

  ; mm0 : 1 2 3 4, so punpck again, add again
  movq mm1, mm0
  punpcklwd mm0, mm7
  punpckhwd mm1, mm7
  paddd mm4, mm0
  paddd mm5, mm1

  add eax, 16
  dec ecx
  jnz @B

  paddd mm5, mm4
  pshufw mm6, mm5, 00001110b ;move high bit of mm5 to mm6
  paddd mm6, mm5
  movd eax, mm6
  emms

  ; calc mean
  ; dividend is 64bit
  mov dword ptr [ebp - 8], eax
  mov dword ptr [ebp - 4], 0
  fild qword ptr [ebp - 8]
  fild dword ptr [ebp + 12]
  fdivp
  
  mov edx, [ebp + 20]
  fstp real8 ptr [edx]
  mov edx, [ebp + 16]
  mov [edx], eax

Error:
  mov eax, -1
Done:
  mov eax, 0
  mov esp, ebp
  pop ebp
  ret
MmxCalcMean endp
  end