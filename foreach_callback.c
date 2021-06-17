#include "base.h"
#include <ctype.h>

/*
 * foreach_callback will:
 *
 * 1. do nothing for multipart parts because gmime automatically
 * descends into subparts,

 * 2. set mf->text_part to the current part if the current part looks
 * more more like plain text than anything seen so far,
 *
 * 3. save a file in pieces/ for the current part.
 */
void
foreach_callback(GMimeObject *parent, GMimeObject *part, gpointer data)
{
  a_mail_file *mf = data;
  if (GMIME_IS_MULTIPART(part))
    return;
  mf->part_count++;
  GMimeContentType *content_type = g_mime_object_get_content_type(part);
  GMimePart *mime_part = (GMimePart *)part;

#define IS(A, B) (0 == strcasecmp(A, B))
  if (IS("text", g_mime_content_type_get_media_type(content_type))) {
    if (0) {
    } else if (g_mime_part_is_attachment(mime_part)) {
      /* An attachment should never become the main body of the email. */
    } else if (g_mime_content_type_get_parameter(content_type, "name")) {
      /*
       * Probably an attachment, such as foo.log.
       *
       * Content-Type: text/plain; charset=US-ASCII; name=20200320_09.log
       * Content-Transfer-Encoding: quoted-printable
       * Content-Disposition: attachment; filename=20200320_09.log
       */
    } else if (!mf->text_part ||
        (IS("plain",
            g_mime_content_type_get_media_subtype(g_mime_object_get_content_type((GMimeObject *)mf->text_part))) &&
         (IS("plain", g_mime_content_type_get_media_subtype(content_type))))) {
      g_object_ref(part);
      if (mf->text_part)
        g_object_unref(mf->text_part);
      mf->text_part = mime_part;
    }
    /* dump(part); */
  }
#undef IS

  char *path = object_to_path(part, mf);
  int x = object_save(part, path, false);
  free(path);
  if (!mf->eno) mf->eno = x;
}
