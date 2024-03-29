/* { dg-do compile } */
/* { dg-options "-O2 -mavx512vl" } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 2 } } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\{\]" 2 } } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vdivpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256d x256;
volatile __m128d x128;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_div_pd (x256, m, x256, x256);
  x256 = _mm256_maskz_div_pd (m, x256, x256);
  x128 = _mm_mask_div_pd (x128, m, x128, x128);
  x128 = _mm_maskz_div_pd (m, x128, x128);
}
