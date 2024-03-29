/* { dg-do compile } */
/* { dg-options "-mavx512bw -mavx512vl -O2" } */
/* { dg-final { scan-assembler "(vpblendmw|vmovdqu16)\[ \\t\]+\[^\n\]*%zmm\[0-9\]\{%k\[1-7\]\}" } } */
/* { dg-final { scan-assembler "(vpblendmw|vmovdqu16)\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}" } } */
/* { dg-final { scan-assembler "(vpblendmw|vmovdqu16)\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}" } } */

#include <immintrin.h>

volatile __m256i x;
volatile __m128i xx;
volatile __m512i xxx;
volatile __mmask8 m;

void extern
avx512bw_test (void)
{
  x = _mm256_mask_blend_epi16 (m, x, x);
  xx = _mm_mask_blend_epi16 (m, xx, xx);
  xxx = _mm512_mask_blend_epi16 (m, xxx, xxx);
}
