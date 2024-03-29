/* { dg-do run } */
/* { dg-options "-O2 -mavx512bw -DAVX512BW" } */
/* { dg-require-effective-target avx512bw } */

#include "avx512f-helper.h"

#define SIZE (AVX512F_LEN / 8)
#include "avx512f-mask-type.h"

void
CALC (MASK_TYPE *r, unsigned char *s1, unsigned char *s2)
{
  int i;
  *r = 0;
  MASK_TYPE one = 1;

  for (i = 0; i < SIZE; i++)
    if (s1[i] == s2[i])
      *r = *r | (one << i);
}

void
TEST (void)
{
  int i;
  UNION_TYPE (AVX512F_LEN, i_b) src1, src2;
  MASK_TYPE res_ref, res1, res2;
  MASK_TYPE mask = MASK_VALUE;
  res1 = 0;
  res2 = 0;

  for (i = 0; i < SIZE / 2; i++)
    {
      src1.a[i * 2] = i;
      src1.a[i * 2 + 1] = i * i;
      src2.a[i * 2] = 2 * i;
      src2.a[i * 2 + 1] = i * i;
    }

  res1 = INTRINSIC (_cmpeq_epu8_mask) (src1.x, src2.x);
  res2 = INTRINSIC (_mask_cmpeq_epu8_mask) (mask, src1.x, src2.x);

  CALC (&res_ref, src1.a, src2.a);

  if (res_ref != res1)
    abort ();

  res_ref &= mask;

  if (res_ref != res2)
    abort ();
}
