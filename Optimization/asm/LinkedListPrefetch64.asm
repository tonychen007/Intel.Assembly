IFDEF ASMX86_64
include <LinkedListPrefetch.inc>
.code

; extern "C" void LlTraverseAVXNoPrefetch(LlNode * p);
; extern "C" void LlTraverseAVXPrefetch(LlNode * p);

_Traverse64 macro UsePrefetch
  mov rax, rcx
  test rax, rax
  jz Done

  align 16
@@:
  mov rcx, [rax + LlNode.Link]
  vmovapd ymm0, ymmword ptr [rax + LlNode.ValA]
  vmovapd ymm1, ymmword ptr [rax + LlNode.ValB]

IFIDNI <UsePrefetch>,<Y>
        mov rdx,rcx
        test rdx,rdx                        ;is there another node?
        cmovz rdx,rax                       ;avoid prefetch of NULL
        prefetchnta [rdx]                   ;prefetch start of next node
ENDIF

  ; ValC = sqrt(a*a + b*b)
  vmulpd ymm2, ymm0, ymm0
  vmulpd ymm3, ymm1, ymm1
  vaddpd ymm4, ymm2, ymm3
  vsqrtpd ymm5, ymm4
  vmovntpd ymmword ptr [rax + LlNode.ValC], ymm5

  ; ValD = sqrt(a/b + b/a)
  vdivpd ymm2, ymm0, ymm1
  vdivpd ymm3, ymm1, ymm0
  vaddpd ymm4, ymm2, ymm3
  vsqrtpd ymm5, ymm4
  vmovntpd ymmword ptr [rax + LlNode.ValD], ymm5

  mov rax, rcx
  test rax, rax
  jnz @B
  vzeroupper

Done:
  ret
endm

LlTraverseAVXNoPrefetch proc
  _Traverse64 n
LlTraverseAVXNoPrefetch endp

LlTraverseAVXPrefetch proc
  _Traverse64 y
LlTraverseAVXPrefetch endp

ENDIF
end