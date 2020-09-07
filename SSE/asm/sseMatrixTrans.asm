.model flat, c

; extern "C" void sseMatrixTrans(Mat4x4 * dst, Mat4x4 * src);
.code
sseMatrixTrans proc
  push ebp
  mov ebp, esp

  mov esi, [ebp + 12]
  mov edi, [ebp + 8]

  ; load src
  movaps xmm0, [esi]
  movaps xmm1, [esi + 16]
  movaps xmm2, [esi + 32]
  movaps xmm3, [esi + 48]

  ; transpose
  ; a4 a3 a2 a1			; xmm0
  ; b4 b3 b2 b1			; xmm1
  ; c4 c3 c2 c1			; xmm2
  ; d4 d3 d2 d1			; xmm3
  movaps xmm4, xmm0

  ; b4 b3 b2 b1			; xmm1
  ; a4 a3 a2 a1			; xmm4
  ; low bit - b2 a2 b1 a1
  unpcklps xmm4, xmm1

  ; a4 a3 a2 a1			; xmm0
  ; b4 b3 b2 b1			; xmm1
  ; high bit - b4 a4 b3 a3
  unpckhps xmm0, xmm1

  ; the same for c and d
  movaps xmm5, xmm2

  ; c4 c3 c2 c1			; xmm5
  ; d4 d4 d2 d1			; xmm3
  ; low bit - d2 c2 d1 c1
  unpcklps xmm5, xmm3

  ; c4 c3 c3 c1			; xmm2
  ; d4 d3 d2 d1			; xmm3
  ; high bit - d4 c4 d3 c3
  unpckhps xmm2, xmm3

  ;
  ; now the matrix is
  ; b4 a4 b3 a3		; xmm0
  ; b4 b3 b2 b1		; xmm1
  ; d4 c4 d3 c3		; xmm2
  ; d4 d3 d2 d1		; xmm3
  ; b2 a2 b1 a1		; xmm4
  ; d2 c2 d1 c1		; xmm5

  ; unmove xmm1, xmm3
  movaps xmm1, xmm4		; b2 a2 b1 a1	; xmm1	
  movlhps xmm4, xmm5 	; d1 c1 b1 a1	; xmm4  ok
  movhlps xmm5, xmm1	    ; d2 c2 b2 a2	; xmm5  ok
  movaps xmm6, xmm0		; b4 a4 b3 a3	; xmm6
  movlhps xmm6, xmm2   	; d3 c3 b3 a3	; xmm6  ok
  movaps xmm7, xmm2		; d4 c4 d3 c3	; xmm7
  movhlps xmm7, xmm0  	; d4 c4 b4 a4	; xmm7  ok

  ; mov back
  movaps [edi], xmm4
  movaps [edi + 16], xmm5
  movaps [edi + 32], xmm6
  movaps [edi + 48], xmm7

  pop ebp
  ret
sseMatrixTrans endp
end