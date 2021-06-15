#include "base.h"

/*
 * Return an appropriate "pieces/<stuff>" for @part.
 */
char *
object_to_path(GMimeObject *part, a_mail_file *mf)
{
  GMimeContentType *content_type = g_mime_object_get_content_type(part);
  const char *name = g_mime_content_type_get_parameter(content_type, "name");
  GMimeContentDisposition *content_disposition = g_mime_object_get_content_disposition(part);
  const char *filename = content_disposition ?
    g_mime_content_disposition_get_parameter(content_disposition, "filename") : name;

  char *suffix = NULL;
  if (filename) {
    suffix = filename_to_suffix(filename);
  } else {
    const char *charset = g_mime_content_type_get_parameter(content_type, "charset");
    const char *abbrev = charset ? charset_to_abbrev(charset) : NULL;
    char *mime_type = g_mime_content_type_get_mime_type(content_type);
    const char *ext = media_type_to_extension(mime_type);
    if (abbrev)
      asprintf(&suffix, "%s.%s", abbrev, ext);
    else
      asprintf(&suffix, "%s", ext);
    if (mime_type) g_free(mime_type);
  }
  char *path = NULL;
  asprintf(&path, "%s.%d.%s", mf->pieces_base, mf->part_count, suffix);
  return path;
}
