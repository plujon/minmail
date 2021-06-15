#pragma once

#define _GNU_SOURCE 1

#include <glib.h>
#include <gmime/gmime.h>

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct a_mail_file {
  const char *path;
  const char *tail;
  char *backup_path;
  char *pieces_base;
  GMimeMessage *message;
  GMimeObject *text_part;
  int part_count;
  int eno;
} a_mail_file;


GMimeMessage *file_to_message(const char *path);
a_mail_file *mail_file_new(const char *path);
char *filename_to_suffix(const char *filename);
char *object_to_path(GMimeObject *part, a_mail_file *mf);
const char *media_type_to_extension(const char *media_type);
int chew(const char *path);
int message_save(GMimeMessage *message, const char *path, bool clobber);
int move_file(const char *src, const char *dest);
int object_save(GMimeObject *object, const char *path, bool clobber);
int usage(int x);
void create_head(a_mail_file *mf);
void foreach_callback(GMimeObject *parent, GMimeObject *part, gpointer data);
void mail_file_fini(a_mail_file **mf);
void min_headers(a_mail_file *mf);
void process_parts(a_mail_file *mf);
void wreak_havok(a_mail_file *mf);

extern int havok;
extern int verbose;

#define NO __LINE__
#define OK 0

#define dbgf(n, fmt, ...)                                               \
  if (n <= verbose) printf(fmt "\n", __VA_ARGS__)

#define woof(fmt, ...)                                                  \
  fprintf(stderr, fmt "\n", __VA_ARGS__)
