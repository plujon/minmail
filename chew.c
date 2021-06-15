#include "base.h"

int
chew(const char *path)
{
  if (0 == verbose) printf(".");
  dbgf(1, "processing %s", path);
  a_mail_file *mf = mail_file_new(path);
  if (!mf) return NO;
  if (0 != access("pieces", F_OK) && 0 != mkdir("pieces", 0777)) {
    woof("failed to create %s %s", "pieces", strerror(errno));
    return NO;
  }
  if (!mf->eno) process_parts(mf);
  if (!mf->eno) create_head(mf);
  if (!mf->eno && havok) wreak_havok(mf);
  int x = mf->eno;
  mail_file_fini(&mf);
  return x;
}

