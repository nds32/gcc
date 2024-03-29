/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vcvtdq2ps\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vcvtdq2ps\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vcvtdq2ps\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vcvtdq2ps\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256i s1;
volatile __m128i s2;
volatile __m256 res1;
volatile __m128 res2;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  res1 = _mm256_mask_cvtepi32_ps (res1, m, s1);
  res2 = _mm_mask_cvtepi32_ps (res2, m, s2);

  res1 = _mm256_maskz_cvtepi32_ps (m, s1);
  res2 = _mm_maskz_cvtepi32_ps (m, s2);
}
