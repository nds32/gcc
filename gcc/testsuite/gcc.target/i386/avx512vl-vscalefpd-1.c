/* { dg-do compile } */
/* { dg-options "-O2 -mavx512vl" } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\[^\{\]" 3 } } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vscalefpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */

#include <immintrin.h>

volatile __m256d x256;
volatile __m128d x128;
volatile __mmask8 m8;

void extern
avx512vl_test (void)
{
  x256 = _mm256_scalef_pd (x256, x256);
  x256 = _mm256_mask_scalef_pd (x256, m8, x256, x256);
  x256 = _mm256_maskz_scalef_pd (m8, x256, x256);
  x128 = _mm_scalef_pd (x128, x128);
  x128 = _mm_mask_scalef_pd (x128, m8, x128, x128);
  x128 = _mm_maskz_scalef_pd (m8, x128, x128);
}
