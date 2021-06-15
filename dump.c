#include "base.h"

void
dump(GMimeObject *object)
{
  if (!object) { printf("null"); return; }
  GMimeContentType *content_type = g_mime_object_get_content_type(object);
  char *mime_type = g_mime_content_type_get_mime_type(content_type);
  const char *charset = g_mime_content_type_get_parameter(content_type, "charset");
  printf("--- %s with charset %s\n", mime_type, charset);
  char *s = g_mime_object_to_string(object, NULL);
  printf("%s\n---\n", s);
}
