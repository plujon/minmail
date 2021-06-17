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
#ifdef NOT_YET_IMPLEMENTED
    g_mime_format_options_set_max_line(g_mime_format_options_get_default(), 996);
#endif
    g_mime_message_set_mime_part(mf->message, (GMimeObject *)mf->text_part);

    /*
     * Ward off quoted-printable from many emails because of its line
     * termination(s) (often at 78 characters).  Such termnination is
     * ugly and poses obstacles to those who want to use grep on their
     * mail.
     */
    GMimeContentEncoding encoding = g_mime_part_get_content_encoding(mf->text_part);
    if (GMIME_CONTENT_ENCODING_DEFAULT != encoding) {
      encoding = g_mime_part_get_best_content_encoding(mf->text_part, GMIME_ENCODING_CONSTRAINT_8BIT);
      g_mime_part_set_content_encoding(mf->text_part, encoding);
    }
    if (GMIME_CONTENT_ENCODING_QUOTEDPRINTABLE == encoding) {
      /*
       * Work around optimization in libgmime and force re-encoding of
       * quoted-printable bodies so that any quoted lines that have
       * been split at 78 characters or so have a chance to grow to
       * their full potential when using a specially built version of
       * libgmime that only splits quoted-printable lines after 996
       * characters.  Long lines make it less likely that grep will
       * fail because the term being searched for happens to have been
       * spl=it.
       */
      g_mime_part_set_content_encoding(mf->text_part, GMIME_CONTENT_ENCODING_DEFAULT);
      char *text = g_mime_text_part_get_text((GMimeTextPart *)mf->text_part);
      dbgf(3, "%s", text);
      g_mime_part_set_content_encoding(mf->text_part, encoding);
      g_mime_text_part_set_text((GMimeTextPart *)mf->text_part, text);
      g_free(text);
    }

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
