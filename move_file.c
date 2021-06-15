#include "base.h"
#include <sys/wait.h>

int
move_file(const char *src, const char *dest)
{
  if (0 == rename(src, dest))
    return OK;
  if (EXDEV == errno) {
    /* need to flush */
    const char *argv[] = { "/bin/cp", src, dest, NULL };
    pid_t child = fork();
    if (child < 0) {
      perror("fork");
      return NO;
    }
    if (0 == child) {
      execv(argv[0], (char **)argv);
      exit(3);
    }
    int status = 0;
    pid_t pid = waitpid(child, &status, 0);
    if (pid == child && WIFEXITED(status) && 0 == WEXITSTATUS(status))
      return OK;
    return NO;
  }
  return NO;
}
