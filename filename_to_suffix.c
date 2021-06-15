#include "base.h"

char clean[] = {
  '_','_','_','_','_','_','_','_',
  '_','_','_','_','_','_','_','_',
  '_','_','_','_','_','_','_','_',
  '_','_','_','_','_','_','_','_',
  '_','!','_','#','$','%','&','\'',
  '(',')','_','+',',','-','.','_',
  '0','1','2','3','4','5','6','7',
  '8','9','_',';','_','=','_','_',
  '@','a','b','c','d','e','f','g',
  'h','i','j','k','l','m','n','o',
  'p','q','r','s','t','u','v','w',
  'x','y','z','[','_',']','^','_',
  '`','a','b','c','d','e','f','g',
  'h','i','j','k','l','m','n','o',
  'p','q','r','s','t','u','v','w',
  'x','y','z','{','_','}','~','_'
};

/*
 * Avoid whitespace, avoid some reserved characters, use lowercase (in
 * ascii range), and limit length of file names.
 */
char *
filename_to_suffix(const char *filename)
{
  if (!*filename)
    return strdup("empty");
  char *s = strndup(filename, 250);
  char *p = s;
  for (; *p; ++p)
    if (0 < *p && *p < sizeof(clean))
      *p = clean[(unsigned)*p];
  if (128 < p - s) {
    p = &s[120];
    strcpy(p, ".trunc");
  }
  return s;
}
