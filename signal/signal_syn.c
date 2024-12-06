#include <stdio.h>      // 用于 printf
#include <stdlib.h>     // 用于 exit
#include <signal.h>     // 用于信号处理，如 sigset_t, sigwaitinfo, sigaction
#include <errno.h>      // 用于 errno 和 strerror
#include <pthread.h>    // 用于线程操作
#include <unistd.h>     // 用于 sleep, getpid
#include <sys/types.h>  // 用于 pthread_t

void sig_handler(int signum)
{
    static int j = 0;
    static int k = 0;
    pthread_t sig_ppid = pthread_self();
    // 显示信号在哪个线程中处理

    if (signum == SIGUSR1) {
        printf("thread %lu, receive SIGUSR1 No. %d\n", sig_ppid, j); // %lu 用于打印 pthread_t
        j++;
    } else if (signum == SIGRTMIN) {
        printf("thread %lu, receive SIGRTMIN No. %d\n", sig_ppid, k);
        k++;
    }
}

void* worker_thread()
{
    pthread_t ppid = pthread_self();
    pthread_detach(ppid);
    while (1) {
        printf("I'm thread %lu, I'm alive\n", ppid);
        sleep(10);
    }
}

void* sigmgr_thread()
{
    sigset_t waitset, oset;
    siginfo_t info;
    int rc;
    pthread_t ppid = pthread_self();

    pthread_detach(ppid);

    sigemptyset(&waitset);
    sigaddset(&waitset, SIGRTMIN);
    sigaddset(&waitset, SIGUSR1);

    while (1)  {
        rc = sigwaitinfo(&waitset, &info);
        if (rc != -1) {
            printf("sigwaitinfo() fetch the signal - %d\n", rc);
            sig_handler(info.si_signo);
        } else {
            printf("sigwaitinfo() returned err: %d; %s\n", errno, strerror(errno));
        }
    }
}


int main()
{
    sigset_t bset, oset;
    int i;
    pid_t pid = getpid();
    pthread_t ppid;

    // 阻塞 SIGRTMIN 和 SIGUSR1，这些信号将在专用线程 sigmgr_thread 中处理
    sigemptyset(&bset);
    sigaddset(&bset, SIGRTMIN);
    sigaddset(&bset, SIGUSR1);
    if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0)
        printf("!! Set pthread mask failed\n");
    
    // 创建 sigmgr_thread 线程，处理 SIGUSR1 和 SIGRTMIN
    pthread_create(&ppid, NULL, sigmgr_thread, NULL);
  
    // 创建 5 个工作线程，继承主线程的线程屏蔽
    for (i = 0; i < 5; i++) {
        pthread_create(&ppid, NULL, worker_thread, NULL);
    }

    // 发送 50 次 SIGUSR1 和 SIGRTMIN 信号
    for (i = 0; i < 50; i++) {
        kill(pid, SIGUSR1);
        printf("main thread, send SIGUSR1 No. %d\n", i);
        kill(pid, SIGRTMIN);
        printf("main thread, send SIGRTMIN No. %d\n", i);
        sleep(10);
    }
    exit(0);
}

