/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vpermps\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vpermps\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpermps\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256i x;
volatile __m256 y;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  y = _mm256_permutexvar_ps (x, y);
  y = _mm256_mask_permutexvar_ps (y, m, x, y);
  y = _mm256_maskz_permutexvar_ps (m, x, y);
}
