/* { dg-do run } */
/* { dg-options "-fsanitize=vla-bound -Wall -Wno-unused-variable -std=c++14" } */
/* { dg-shouldfail "ubsan" } */

int
main (void)
{
  int y = -18;
  int a[y];
  return 0;
}

/* { dg-output "terminate called after throwing an instance" } */
