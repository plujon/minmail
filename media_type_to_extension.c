#include "base.h"

const char *
media_type_to_extension(const char *media_type)
{
#define X(A, B) if (!strcasecmp(A, media_type)) return B;
#include "_extensions.c"
#undef X
  char *ext = strdup(media_type);
  char *slash = strchr(ext, '/');
  if (slash) *slash = '-';
  return ext; /* this memory will be leaked; owell */
}
