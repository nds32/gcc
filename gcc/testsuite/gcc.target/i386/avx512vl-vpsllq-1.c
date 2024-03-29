/* { dg-do compile } */
/* { dg-options "-O2 -mavx512vl" } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 2 } } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\{\]" 4 } } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vpsllq\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>
volatile __m256i x256;
volatile __m128i x128;
volatile __mmask8 m256;
volatile __mmask8 m128;

void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_sll_epi64 (x256, m256, x256, x128);
  x256 = _mm256_maskz_sll_epi64 (m256, x256, x128);
  x128 = _mm_mask_sll_epi64 (x128, m128, x128, x128);
  x128 = _mm_maskz_sll_epi64 (m128, x128, x128);
}
