#include "base.h"

GMimeMessage *
file_to_message(const char *path)
{
  GMimeStream *stream = g_mime_stream_file_open(path, "r", NULL);
  if (!stream) {
    woof("failed to open %s: %s", path, strerror(errno));
    return NULL;
  }
  GMimeParser *parser = g_mime_parser_new_with_stream(stream);
  g_object_unref(stream);
  GMimeMessage *message = g_mime_parser_construct_message(parser, NULL);
  g_object_unref(parser);
  return message;
}
