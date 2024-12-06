#include <stdio.h>      // 用于 printf
#include <stdlib.h>     // 用于 exit 函数
#include <string.h>     // 用于字符串处理（如 memset 等）
#include <sys/types.h>  // 用于 mkfifo 和 open 函数
#include <sys/stat.h>   // 用于 mkfifo 函数
#include <fcntl.h>      // 用于 open 函数
#include <unistd.h>     // 用于 read 和 close 函数

int main() {
    const char *fifoPath = "/tmp/my_fifo";
    mkfifo(fifoPath, 0666);  // 创建有名管道
    char buf[1024];
    int fd;
    
    // 永久循环，持续监听有名管道
    while (1) {
        fd = open(fifoPath, O_RDONLY);  // 打开管道进行读取
        read(fd, buf, sizeof(buf));

        // 打印接收到的消息
        printf("Received: %s\n", buf);
        close(fd);
    }
    
    return 0;
}

