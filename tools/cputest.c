#include <stdio.h>
#include <time.h>

#define __USE_GNU  //启用CPU_ZERO等相关的宏
#include <pthread.h>

#define SLEEP_UNIT 10000

int g_working = 0;

void thread_loop(void *ptr) {
  while (1) {
    if (!g_working) {
      usleep(1);
    }
  }
}

void thread_work(void *ptr) {
  unsigned long work_time, sleep_time, cpu_percent;

  if (NULL == ptr) return;

  cpu_percent = *(unsigned long *)ptr;
  if (cpu_percent > 100) cpu_percent = 100;

  work_time = cpu_percent * SLEEP_UNIT;
  sleep_time = 100 * SLEEP_UNIT - work_time;

  while (1) {
    g_working = 1;
    usleep(work_time);
    g_working = 0;
    usleep(sleep_time);
  }
}

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2;
  unsigned long cpu_percent = 50;

  if (argc > 1) {
    int temp = atoi(argv[1]);
    if (temp >= 0 && temp <= 100) {
      cpu_percent = temp;
    }
  }

  if (argc > 2) {
    cpu_set_t mask;
    int temp = atoi(argv[2]);

    CPU_ZERO(&mask);
    CPU_SET(temp, &mask);
    if (sched_setaffinity(44, sizeof(mask), &mask) == -1) {
      printf("sched_setaffinity fail!\n");
    }
  }

  if (pthread_create(&tid1, NULL, (void *)&thread_loop, NULL)) {
    printf("pthread_create fail!\n");
    return 0;
  }

  if (pthread_create(&tid2, NULL, (void *)&thread_work, (void *)&cpu_percent)) {
    printf("pthread_create fail!\n");
    return 0;
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}