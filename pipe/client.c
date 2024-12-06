#include <stdio.h>      // 用于 printf, fgets
#include <stdlib.h>     // 用于 exit
#include <string.h>     // 用于 strlen
#include <sys/types.h>  // 用于 open 函数
#include <sys/stat.h>   // 用于 open 函数
#include <fcntl.h>      // 用于 open 函数
#include <unistd.h>     // 用于 write 和 close 函数

int main() {
    const char *fifoPath = "/tmp/my_fifo";
    char buf[1024];
    int fd;
    
    // 获取要发送的消息
    printf("Enter message: ");
    fgets(buf, sizeof(buf), stdin);
    
    fd = open(fifoPath, O_WRONLY);  // 打开管道进行写入
    write(fd, buf, strlen(buf) + 1);
    close(fd);
    
    return 0;
}

