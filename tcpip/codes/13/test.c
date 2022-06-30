#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void handle_child(int sig) {
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) >
         0) { /*对结束的子进程进行善后处理*/
  }
}

int main(void) {
  int procnum = 10, loopnum = 10;
  int i = 0, j = 0;
  pid_t fpid;

  for (i = 0; i < procnum; i++) {
    fpid = fork();
    // printf("child pid: %d\n", getpid());
    if (fpid == 0) {
      for (j = 0; j < loopnum; j++) {
        printf("loop %d\n", j);
      }
      exit(0);
    }
  }

  while (1) {
  }
  sleep(1000);
  printf("parrent pid: %d\n", getpid());

  return 0;
}