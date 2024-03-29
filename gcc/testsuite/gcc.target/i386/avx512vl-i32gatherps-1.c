/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vgatherdps\[ \\t\]+\[^\n\]*ymm\[0-9\]\[^\n\]*ymm\[0-9\]{%k\[1-7\]}" 2 } } */
/* { dg-final { scan-assembler-times "vgatherdps\[ \\t\]+\[^\n\]*xmm\[0-9\]\[^\n\]*xmm\[0-9\]{%k\[1-7\]}" 2 } } */

#include <immintrin.h>

volatile __m256 x1;
volatile __m128 x2;
volatile __m256i idx1;
volatile __m128i idx2;
volatile __mmask8 m8;
float *base;

void extern
avx512vl_test (void)
{
  x1 = _mm256_mmask_i32gather_ps (x1, 0xFF, idx1, base, 8);
  x1 = _mm256_mmask_i32gather_ps (x1, m8, idx1, base, 8);
  x2 = _mm_mmask_i32gather_ps (x2, 0xFF, idx2, base, 8);
  x2 = _mm_mmask_i32gather_ps (x2, m8, idx2, base, 8);
}
