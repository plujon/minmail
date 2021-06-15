#include "base.h"

void
mail_file_fini(a_mail_file **pmf)
{
  a_mail_file *mf = *pmf;
  *pmf = NULL;
  if (mf->backup_path) free(mf->backup_path);
  if (mf->pieces_base) free(mf->pieces_base);
  if (mf->message) g_object_unref(mf->message);
  if (mf->text_part) g_object_unref(mf->text_part);
  free(mf);
}
