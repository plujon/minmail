#include "base.h"

int
usage(int x)
{
  const char *s =
#include "_usage.c"
      ;
  fprintf(x ? stderr : stdout, "%s", s);
  return x;
}
