#include "base.h"

int
message_save(GMimeMessage *message, const char *path, bool clobber)
{
  if (!clobber && 0 == access(path, F_OK))
    return OK;
  dbgf(2, "saving %s", path);
  GMimeStream *stream = g_mime_stream_file_open(path, "w", NULL);
  if (!stream) {
    woof("failed to open %s %s", path, strerror(errno));
    return NO;
  }
  int ret = 0;
  if (g_mime_object_write_to_stream((GMimeObject *)message, NULL, stream) < 0) {
    woof("failed to write %s %s", path, strerror(errno));
    ret = NO;
  }
  if (0 == ret)
    g_mime_stream_flush(stream);
  g_object_unref(stream);
  if (access(path, F_OK)) woof("wtf %s", path);
  return ret;
}
