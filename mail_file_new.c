#include "base.h"

a_mail_file *
mail_file_new(const char *path)
{
  a_mail_file *mf = (a_mail_file *)calloc(1, sizeof(a_mail_file));

  mf->path = path;

  const char *slash = strrchr(path, '/');
  mf->tail = slash ? slash + 1 : path;

  mf->message = file_to_message(path);

  if (!mf->message) {
    free(mf);
    return NULL;
  }

  if (havok)
    asprintf(&mf->backup_path, "pieces/%s", mf->tail);

  if (!mf->pieces_base) {
    GDateTime *datetime = g_mime_message_get_date(mf->message);
    if (!datetime)
      datetime = g_date_time_new_utc(1970, 0, 1, 0, 0, 0.0);
    InternetAddressList *addresses = g_mime_message_get_from(mf->message);
    InternetAddress *address = internet_address_list_get_address(addresses, 0);
    const char *email =
      internet_address_mailbox_get_addr((InternetAddressMailbox *)address);
    char *ymd_hms = g_date_time_format(datetime, "%Y%m%d.%H%M%S");
    asprintf(&mf->pieces_base, "pieces/%s.%s", ymd_hms, email);
    g_free(ymd_hms);
  }

  return mf;
}
