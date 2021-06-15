#include "base.h"

void
create_head(a_mail_file *mf)
{
  GMimeTextPart *body = g_mime_text_part_new_with_subtype("plain");
  g_mime_text_part_set_text(body, "");
  g_mime_message_set_mime_part(mf->message, (GMimeObject *)body);
  char *path = NULL;
  asprintf(&path, "%s.%s", mf->pieces_base, "head");
  if (!mf->eno) mf->eno = message_save(mf->message, path, false);
  free(path);
}
