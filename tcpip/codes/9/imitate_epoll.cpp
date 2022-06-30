#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFEFR_SIZE 1024

struct fds {
  int epollfd;
  int sockfd;
};
void reset_oneshot(int epollfd, int fd) {
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
  epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}
int setnonblocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  fcntl(fd, F_SETFL, new_option);
  return old_option;
}

void addfd(int epolled, int fd, bool oneshot) {
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  if (oneshot) {
    event.events |= EPOLLONESHOT;
  }
  epoll_ctl(epolled, EPOLL_CTL_ADD, fd, &event);
  setnonblocking(fd);
}

void* worker(void* arg) {
  int sockfd = ((fds*)arg)->sockfd;
  int epollfd = ((fds*)arg)->epollfd;
  printf("start new thread to receive data on fd: %d\n", sockfd);
  char buf[BUFFEFR_SIZE];
  memset(buf, '\0', sizeof(buf));
  while (1) {
    int ret = recv(sockfd, buf, BUFFEFR_SIZE - 1, 0);
    if (ret == 0) {
      close(sockfd);
      printf("foreiner closed the connection\n");
      break;
    } else if (ret < 0) {
      if (errno == EAGAIN) {
        reset_oneshot(epollfd, sockfd);
        printf("read later\n");
        break;
      }
    } else {
      printf("get content: %s\n", buf);
      sleep(5);
    }
  }
}
int main(int argc, const char* argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }
  const char* ip = argv[1];
  int port = atoi(argv[2]);

  int ret = 0;
  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &address.sin_addr);
  address.sin_port = htons(port);
  int listenfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(listenfd >= 0);
  ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
  assert(ret != -1);
  ret = listen(listenfd, 5);
  assert(ret != -1);
  epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  addfd(epollfd, listenfd, false);
  while (1) {
    int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (ret < 0) {
      printf("test\n");
      break;
    }
    for (int i = 0; i < ret; i++) {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd) {
        struct sockaddr_in client_address;
        socklen_t client_addrlength = sizeof(client_address);
        int connfd = accept(listenfd, (struct sockaddr*)&client_address,
                            &client_addrlength);
        addfd(epollfd, connfd, true);
      } else if (events[i].events & EPOLLIN) {
        pthread_t thread;
        fds fds_for_new_worker;
        fds_for_new_worker.epollfd = epollfd;
        fds_for_new_worker.sockfd = sockfd;
        pthread_create(&thread, NULL, worker, (void*)&fds_for_new_worker);

      } else {
        printf("someting else happend\n");
      }
    }
  }
}