IFDEF ASMX86_32
include <LinkedListPrefetch.inc>
.model flat,c
.code

; extern "C" void LlTraverseAVXNoPrefetch(LlNode * p);
; extern "C" void LlTraverseAVXPrefetch(LlNode * p);

_Traverse32 macro UsePrefetch
  mov eax, [esp + 4]
  test eax, eax
  jz Done

  align 16
@@:
  mov ecx, [eax + LlNode.Link]
  vmovapd ymm0, ymmword ptr [eax + LlNode.ValA]
  vmovapd ymm1, ymmword ptr [eax + LlNode.ValB]

IFIDNI <UsePrefetch>,<Y>
        mov edx,ecx
        test edx,edx                        ;is there another node?
        cmovz edx,eax                       ;avoid prefetch of NULL
        prefetchnta [edx]                   ;prefetch start of next node
ENDIF

  ; ValC = sqrt(a*a + b*b)
  vmulpd ymm2, ymm0, ymm0
  vmulpd ymm3, ymm1, ymm1
  vaddpd ymm4, ymm2, ymm3
  vsqrtpd ymm5, ymm4
  vmovntpd ymmword ptr [eax + LlNode.ValC], ymm5

  ; ValD = sqrt(a/b + b/a)
  vdivpd ymm2, ymm0, ymm1
  vdivpd ymm3, ymm1, ymm0
  vaddpd ymm4, ymm2, ymm3
  vsqrtpd ymm5, ymm4
  vmovntpd ymmword ptr [eax + LlNode.ValD], ymm5

  mov eax, ecx
  test eax, eax
  jnz @B
  vzeroupper

Done:
  ret
endm

LlTraverseAVXNoPrefetch proc
  _Traverse32 n
LlTraverseAVXNoPrefetch endp

LlTraverseAVXPrefetch proc
  _Traverse32 y
LlTraverseAVXPrefetch endp

ENDIF
end