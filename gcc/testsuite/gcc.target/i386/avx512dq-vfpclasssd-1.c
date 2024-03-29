/* { dg-do compile } */
/* { dg-options "-mavx512dq -O2" } */
/* { dg-final { scan-assembler "vfpclasssd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\n^k\]*%k\[1-7\]\[^\{\]" } } */

#include <immintrin.h>

volatile __m128d x128;
volatile __mmask8 m8;

void extern
avx512dq_test (void)
{
  m8 = _mm_fpclass_sd_mask (x128, 13);
}
