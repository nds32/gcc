/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vpabsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */

#include <immintrin.h>

volatile __m256i xx;
volatile __m128i x2;

void extern
avx512vl_test (void)
{
  xx = _mm256_abs_epi64 (xx);
  xx = _mm256_mask_abs_epi64 (xx, 2, xx);
  xx = _mm256_maskz_abs_epi64 (2, xx);
  x2 = _mm_abs_epi64 (x2);
  x2 = _mm_mask_abs_epi64 (x2, 2, x2);
  x2 = _mm_maskz_abs_epi64 (2, x2);
}
