/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vcvttpd2dqy\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vcvttpd2dqx\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vcvttpd2dqy\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vcvttpd2dqx\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256d s1;
volatile __m128d s2;
volatile __m128i res;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  res = _mm256_mask_cvttpd_epi32 (res, m, s1);
  res = _mm_mask_cvttpd_epi32 (res, m, s2);

  res = _mm256_maskz_cvttpd_epi32 (m, s1);
  res = _mm_maskz_cvttpd_epi32 (m, s2);
}
