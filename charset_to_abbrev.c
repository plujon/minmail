#include "base.h"

const char *
charset_to_abbrev(const char *charset)
{
  if (!charset) return NULL;
#define X(A, B) if (!strcasecmp(A, charset)) return B;
#include "_charsets.c"
#undef X
  return charset;
}
