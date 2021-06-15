#include "base.h"

void
process_parts(a_mail_file *mf)
{
  mf->part_count = 0;
  g_mime_message_foreach((GMimeMessage *)mf->message, foreach_callback, mf);
}
