/* { dg-do compile } */
/* { dg-options "-mavx512vl -mavx512bw -O2" } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpminsq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256i x;
volatile __m128i y;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  x = _mm256_min_epi64 (x, x);
  x = _mm256_mask_min_epi64 (x, m, x, x);
  x = _mm256_maskz_min_epi64 (m, x, x);
  y = _mm_min_epi64 (y, y);
  y = _mm_mask_min_epi64 (y, m, y, y);
  y = _mm_maskz_min_epi64 (m, y, y);
}
