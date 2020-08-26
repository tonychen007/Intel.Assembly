.model flat, c

.const
StartMinVal qword 0ffffffffffffffffh
StartMaxVal qword  0000000000000000h

; extern "C" int MmxCalcMinMax(Uint8 * x, int n, Uint8 * umin, Uint8 * umax);
; retun:	 -1 "invalid n"
;			  0 "success"

.code
extern NMIN:dword

MmxCalcMinMax proc
  push ebp
  mov  ebp, esp

  mov ecx, [ebp + 12]
  cmp ecx, NMIN
  jle Error
  test ecx, 0Fh
  jnz Error

  ; init
  shr ecx, 4		; 16 bytes block
  mov edx, [ebp + 8]
  movq mm4, StartMinVal
  movq mm6, mm4
  movq mm5, StartMaxVal
  movq mm7, mm5

@@:
  movq mm0, [edx]
  movq mm1, [edx + 8]
  pminub mm6, mm0
  pminub mm4, mm1
  pmaxub mm7, mm0
  pmaxub mm5, mm1
  add edx, 16
  dec ecx
  jnz @B

  ; now min, max value is in mm4, mm6 and mm5, mm7 respectively
  pminub mm6, mm4				; final 8 vals
  pshufw mm0, mm6, 00001110b	
  pminub mm6, mm0				; final 4 vals
  pshufw mm0, mm6, 00000001b	
  pminub mm6, mm0				; final 2 vals
  pextrw eax, mm6, 0
  ; now 2 min vals is in ax
  cmp al, ah  
  jbe @F
  mov al, ah
@@:  
  mov [ebp + 16], al
  jmp Done

  ; the same for max value
  pmaxub mm7, mm5				; final 8 vals
  pshufw mm0, mm7, 00001110b	
  pminub mm7, mm0				; final 4 vals
  pshufw mm0, mm7, 00000001b	
  pminub mm7, mm0				; final 2 vals
  pextrw eax, mm7, 0
  ; now 2 min vals is in ax
  cmp al, ah  
  jae @F
  mov al, ah
@@:  
  mov [ebp + 20], al
  jmp Done
Error:
  mov eax, -1
Done:
  emms
  mov eax, 0
  pop ebp
  ret
MmxCalcMinMax endp
  end