#include "base.h"

int havok;
int verbose;

#define IS(S) !strcmp(S, *argv)

int main(int argc, char *argv[])
{
  --argc; ++argv;
  if (argc < 1) return usage(1);
  g_mime_init();
  for (; 0 < argc; --argc, ++argv) {
    if (0) {}
    else if (IS("-h")) return usage(0);
    else if (IS("-q")) --verbose;
    else if (IS("-v")) ++verbose;
    else if (IS("--wreak-havok")) { woof("%s", "havok!"); ++havok; }
    else if (chew(*argv)) return 1;
  }
  return 0;
}

#undef IS
