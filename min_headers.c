#include "base.h"

/* abritrary list of headers that are not particularly useful to me */
const char *losers[] = {
  "ARC-Authentication-Results",
  "ARC-Message-Signature",
  "ARC-Seal",
  "Authentication-Results",
  "DKIM-Signature",
  "Received-SPF",
  "X-Gm-Message-State",
  "X-Google-DKIM-Signature",
  "X-Google-Smtp-Source",
  "X-ZohoMail-DKIM",
  "X-ZohoMail-Owner",
  "X-Zoho-Virus-Status"
};

void
min_headers(a_mail_file *mf)
{
  GMimeObject *message = (GMimeObject *)mf->message;
  for (unsigned i = 0; i < (sizeof(losers)/sizeof(losers[0])); ++i) {
    if (g_mime_object_remove_header(message, losers[i])) {
      dbgf(3, "removed %s", losers[i]);
    }
  }
  if (!g_mime_object_get_header(message, "X-MinMail"))
    g_mime_object_append_header(message, "X-MinMail", "0.0.1", "us-ascii");
}
