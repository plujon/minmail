#include "base.h"

int
object_save(GMimeObject *object, const char *path, bool clobber)
{
  if (GMIME_IS_MESSAGE(object))
    return message_save((GMimeMessage *)object, path, clobber);

  if (GMIME_IS_MESSAGE_PART(object)) {
    /* attached rfc8222 message */
    GMimeMessage *message =
      g_mime_message_part_get_message((GMimeMessagePart *)object);
    return message_save(message, path, clobber);
  }

  if (GMIME_IS_MESSAGE_PARTIAL(object)) {
    woof("%s", "unprepared for message partial");
    return NO;
  }

  if (GMIME_IS_MULTIPART(object)) {
    woof("%s", "unprepared for message partial");
    return NO;
  }

  if (!GMIME_IS_PART(object)) {
    woof("%s", "expected part");
    return NO;
  }
  GMimePart *part = (GMimePart *)object;

  if (!clobber && 0 == access(path, F_OK))
    return OK;

  dbgf(2, "saving %s", path);

  GMimeStream *ostream = g_mime_stream_file_open(path, "w", NULL);
  if (!ostream) {
    woof("failed to open %s", path);
    return NO;
  }

  GMimeContentEncoding encoding =
    g_mime_part_get_content_encoding(part);
  GMimeStream *fstream = g_mime_stream_filter_new(ostream);
  {
    GMimeFilter *filter = g_mime_filter_basic_new(encoding, FALSE);
    g_mime_stream_filter_add((GMimeStreamFilter *)fstream, filter);
    g_object_unref(filter);
  }

  ssize_t x = g_mime_object_write_content_to_stream(object, NULL, fstream);

  g_object_unref(ostream);
  g_object_unref(fstream);

  if (x < 0) {
    woof("failed to write to %s", path);
    unlink(path);
    return NO;
  }

  return OK;
}
