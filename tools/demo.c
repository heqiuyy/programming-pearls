#include <fcntl.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void init_daemon(void)

{
  int pid;

  int i;

  if (pid = fork())

    exit(0);  //是父进程，结束父进程,摆脱会话组长身份。

  else if (pid < 0)

    exit(1);  // fork失败，退出

  //是第一子进程，后台继续执行

  setsid();

  //第一子进程成为新的会话组长和进程组长

  //并与控制终 端分离

  if (pid = fork())

    exit(0);  //是第一子进程，结束第一子进程

  else if (pid < 0)

    exit(1);  // fork失败，退出

  //是第二子进程，继续

  //第二子进程不再是会话组长，也就不会请求打开控制终端。

  for (i = 0; i < NOFILE; ++i)

    //关闭打开的文件描述符

    close(i);

  chdir("/tmp");  //改变工作目录到/tmp

  umask(0);  //重设 文件创建掩模

  return;
}
int main()

{
  FILE *fp;
  time_t t;

  init_daemon();  //初始化为Daemon

  while (1)  //每隔一分钟向test.log报告运行状态

  {
    sleep(60);  //睡 眠一分钟

    if ((fp = fopen("test.log", "a")) >= 0)

    {
      t = time(0);

      fprintf(fp, "Im here at %sn", asctime(localtime(&t)));

      fclose(fp);
    }
  }
}