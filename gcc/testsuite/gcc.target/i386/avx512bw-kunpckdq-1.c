/* { dg-do compile } */
/* { dg-options "-mavx512bw -O2" } */
/* { dg-final { scan-assembler-times "kunpckdq\[ \\t\]+\[^\n\]*%k\[1-7\]" 1 } } */

#include <immintrin.h>

void
avx512bw_test () {
  __mmask64 k1, k2, k3;
  volatile __m512i x;

  __asm__( "kmovq %1, %0" : "=k" (k1) : "r" (1) );
  __asm__( "kmovq %1, %0" : "=k" (k2) : "r" (2) );

  k3 = _mm512_kunpackd (k1, k2);
  x = _mm512_mask_avg_epu8 (x, k3, x, x);
}
