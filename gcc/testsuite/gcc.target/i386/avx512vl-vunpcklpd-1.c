/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vunpcklpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vunpcklpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\{z\}" 1 } } */
/* { dg-final { scan-assembler-times "vunpcklpd\[ \\t\]+\[^\n\]*%ymm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */
/* { dg-final { scan-assembler-times "vunpcklpd\[ \\t\]+\[^\n\]*%xmm\[0-9\]\{%k\[1-7\]\}\[^\{\]" 1 } } */

#include <immintrin.h>

volatile __m256d yy, y2, y3;
volatile __m128d xx, x2, x3;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  yy = _mm256_mask_unpacklo_pd (yy, m, y2, y3);
  xx = _mm_mask_unpacklo_pd (xx, m, x2, x3);

  yy = _mm256_maskz_unpacklo_pd (m, y2, y3);
  xx = _mm_maskz_unpacklo_pd (m, x2, x3);
}
