/* { dg-do compile } */
/* { dg-options "-O2 -mavx512vl" } */
/* { dg-final { scan-assembler "vpcmpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\n^k\]*%k\[1-7\]\[^\{\]" } } */
/* { dg-final { scan-assembler "vpcmpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\n^k\]*%k\[1-7\]\{" } } */
/* { dg-final { scan-assembler "vpcmpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\n^k\]*%k\[1-7\]\[^\{\]" } } */
/* { dg-final { scan-assembler "vpcmpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\n^k\]*%k\[1-7\]\{" } } */

#include <immintrin.h>

volatile __m256i x;
volatile __m128i xx;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  m = _mm256_cmp_epi32_mask (x, x, _MM_CMPINT_EQ);
  m = _mm256_mask_cmp_epi32_mask (m, x, x, _MM_CMPINT_EQ);
  m = _mm_cmp_epi32_mask (xx, xx, _MM_CMPINT_EQ);
  m = _mm_mask_cmp_epi32_mask (m, xx, xx, _MM_CMPINT_EQ);
}
