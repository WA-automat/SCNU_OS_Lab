#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"

int main (int argc, char *argv[]) {
    int ptoc_fd[2], ctop_fd[2];
    pipe(ptoc_fd);
    pipe(ctop_fd);
    char buf[8];
    if (fork() == 0) {					// 子进程
        read(ptoc_fd[0], buf, 4);			// 从父进程读取ping
        printf("%d: received %s\n", getpid(), buf);
        write(ctop_fd[1], "pong", strlen("pong"));	// 向父进程发送pong
    } else {						// 父进程
        write(ptoc_fd[1], "ping", strlen("ping"));	// 父进程向子进程发送ping
        wait(NULL);
        read(ctop_fd[0], buf, 4);			// 从子进程读取pong
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}
