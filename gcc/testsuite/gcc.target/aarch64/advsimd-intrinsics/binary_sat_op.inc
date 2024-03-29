/* Template file for saturating binary operator validation.

   This file is meant to be included by the relevant test files, which
   have to define the intrinsic family to test. If a given intrinsic
   supports variants which are not supported by all the other
   saturating binary operators, these can be tested by providing a
   definition for EXTRA_TESTS.  */

#include <arm_neon.h>
#include "arm-neon-ref.h"
#include "compute-ref-data.h"

#define FNNAME1(NAME) exec_ ## NAME
#define FNNAME(NAME) FNNAME1(NAME)

void FNNAME (INSN_NAME) (void)
{
  /* vector_res = OP(vector1,vector2), then store the result.  */

#define TEST_BINARY_SAT_OP1(INSN, Q, T1, T2, W, N, EXPECTED_CUMULATIVE_SAT, CMT) \
  Set_Neon_Cumulative_Sat(0);						\
  VECT_VAR(vector_res, T1, W, N) =					\
    INSN##Q##_##T2##W(VECT_VAR(vector1, T1, W, N),			\
		      VECT_VAR(vector2, T1, W, N));			\
    vst1##Q##_##T2##W(VECT_VAR(result, T1, W, N),			\
		      VECT_VAR(vector_res, T1, W, N));			\
      CHECK_CUMULATIVE_SAT(TEST_MSG, T1, W, N, EXPECTED_CUMULATIVE_SAT, CMT)

#define TEST_BINARY_SAT_OP(INSN, Q, T1, T2, W, N, EXPECTED_CUMULATIVE_SAT, CMT) \
  TEST_BINARY_SAT_OP1(INSN, Q, T1, T2, W, N, EXPECTED_CUMULATIVE_SAT, CMT)

  DECL_VARIABLE_ALL_VARIANTS(vector1);
  DECL_VARIABLE_ALL_VARIANTS(vector2);
  DECL_VARIABLE_ALL_VARIANTS(vector_res);

  clean_results ();

  /* Initialize input "vector1" from "buffer".  */
  TEST_MACRO_ALL_VARIANTS_2_5(VLOAD, vector1, buffer);

  /* Choose arbitrary initialization values.  */
  VDUP(vector2, , int, s, 8, 8, 0x11);
  VDUP(vector2, , int, s, 16, 4, 0x22);
  VDUP(vector2, , int, s, 32, 2, 0x33);
  VDUP(vector2, , int, s, 64, 1, 0x44);
  VDUP(vector2, , uint, u, 8, 8, 0x55);
  VDUP(vector2, , uint, u, 16, 4, 0x66);
  VDUP(vector2, , uint, u, 32, 2, 0x77);
  VDUP(vector2, , uint, u, 64, 1, 0x88);

  VDUP(vector2, q, int, s, 8, 16, 0x11);
  VDUP(vector2, q, int, s, 16, 8, 0x22);
  VDUP(vector2, q, int, s, 32, 4, 0x33);
  VDUP(vector2, q, int, s, 64, 2, 0x44);
  VDUP(vector2, q, uint, u, 8, 16, 0x55);
  VDUP(vector2, q, uint, u, 16, 8, 0x66);
  VDUP(vector2, q, uint, u, 32, 4, 0x77);
  VDUP(vector2, q, uint, u, 64, 2, 0x88);

  /* Apply a saturating binary operator named INSN_NAME.  */
  TEST_BINARY_SAT_OP(INSN_NAME, , int, s, 8, 8, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , int, s, 16, 4, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , int, s, 32, 2, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , int, s, 64, 1, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , uint, u, 8, 8, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , uint, u, 16, 4, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , uint, u, 32, 2, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, , uint, u, 64, 1, expected_cumulative_sat, "");

  TEST_BINARY_SAT_OP(INSN_NAME, q, int, s, 8, 16, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, int, s, 16, 8, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, int, s, 32, 4, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, int, s, 64, 2, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, uint, u, 8, 16, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, uint, u, 16, 8, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, uint, u, 32, 4, expected_cumulative_sat, "");
  TEST_BINARY_SAT_OP(INSN_NAME, q, uint, u, 64, 2, expected_cumulative_sat, "");

  CHECK_RESULTS (TEST_MSG, "");

#ifdef EXTRA_TESTS
  EXTRA_TESTS();
#endif
}

int main (void)
{
  FNNAME (INSN_NAME) ();

  return 0;
}
