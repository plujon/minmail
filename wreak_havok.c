#include "base.h"

/*
 * wreak_havok will replace the mail file with a minimal version.  A
 * single backup will be saved to pieces/<tail>.  If a file already
 * exists at pieces/<tail>, assume it is the original minted backup
 * and do not replace it.
 */
void
wreak_havok(a_mail_file *mf)
{
  char *path = NULL;
  if (!mf->eno && mf->text_part) {
    g_mime_message_set_mime_part(mf->message, mf->text_part);
    min_headers(mf);

    asprintf(&path, "%s.tmp", mf->backup_path);
    mf->eno = message_save(mf->message, path, true);
    if (mf->eno) {
      goto end;
    }

    /* create 1 and only 1 backup */
    if (0 != access(mf->backup_path, F_OK) &&
        (ENOENT != errno || move_file(mf->path, mf->backup_path))) {
      woof("failed to backup %s : %s", mf->backup_path, strerror(errno));
      mf->eno = NO;
      unlink(path);
      goto end;
    }

    if (move_file(path, mf->path)) {
      woof("failed to move %s to %s : (%d) %s", path, mf->path, errno, strerror(errno));
      mf->eno = NO;
      goto end;
    }
  }
 end:
  free(path);
}
