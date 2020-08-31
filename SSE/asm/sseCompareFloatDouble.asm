.model flat, c

.code
; extern "C" void sseCompareFloat(float a, float b, bool* result);
; extern "C" void sseCompareDouble(double a, double b, bool* result);

sseCompareFloat proc
  push ebp
  mov ebp, esp

  movss xmm0, real4 ptr [ebp + 8]
  movss xmm1, real4 ptr [ebp + 12]
  mov edx, [ebp + 16]

  comiss xmm0, xmm1
  setp byte ptr [edx]	; PF = 1, if unordered. So, the remaining cpm is abandoned.
  jnp @F
  xor al, al

  ; default value 0
  mov byte ptr [edx + 1], al
  mov byte ptr [edx + 2], al
  mov byte ptr [edx + 3], al
  mov byte ptr [edx + 4], al
  mov byte ptr [edx + 5], al
  mov byte ptr [edx + 6], al
  jmp Done

  ; const char* cmp_ops_Str[cmp_ops] = {
  ;	"UO(unordered compare","Less than", "Less than or equal", "Equal",
  ;	"Not Equal", "Greater than", "Greater than or equal" };
@@:
  setb byte ptr [edx + 1]
  setbe byte ptr [edx + 2]
  sete byte ptr [edx + 3]
  setne byte ptr [edx + 4]
  seta byte ptr [edx + 5]
  setae byte ptr [edx + 6]

Done:
  pop ebp
  ret
sseCompareFloat endp

sseCompareDouble proc
  push ebp
  mov ebp, esp

  movsd xmm0, real8 ptr [ebp + 8]
  movsd xmm1, real8 ptr [ebp + 16]
  mov edx, [ebp + 24]

  comisd xmm0, xmm1
  setp byte ptr [edx]	; PF = 1, if unordered. So, the remaining cpm is abandoned.
  jnp @F
  xor al, al
  
  ; default value 0
  mov byte ptr [edx + 1], al
  mov byte ptr [edx + 2], al
  mov byte ptr [edx + 3], al
  mov byte ptr [edx + 4], al
  mov byte ptr [edx + 5], al
  mov byte ptr [edx + 6], al
  jmp Done

  ; const char* cmp_ops_Str[cmp_ops] = {
  ;	"UO(unordered compare","Less than", "Less than or equal", "Equal",
  ;	"Not Equal", "Greater than", "Greater than or equal" };
@@:
  setb byte ptr [edx + 1]
  setbe byte ptr [edx + 2]
  sete byte ptr [edx + 3]
  setne byte ptr [edx + 4]
  seta byte ptr [edx + 5]
  setae byte ptr [edx + 6]

Done:
  pop ebp
  ret
sseCompareDouble endp

end