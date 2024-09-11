#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

void getPrime (int listenfd) {
	int process_num = 0;
	int forked = 0;
	int passed_num = 0;
	int pipes[2];
	while (1) {
		int read_bytes = read(listenfd, &passed_num, 4);	// 从父进程读取数字
		
		if (read_bytes == 0) {					// 读取不到数字
			close(listenfd);
			if (forked) {
				close(pipes[1]);
				int child_pid;
				wait(&child_pid);
			}
			exit(0);
		}
		
		if (process_num == 0) {					// 该进程第一次读取到数字
			process_num = passed_num;
			printf("prime %d\n", process_num);
		}
		
		if (passed_num % process_num != 0) {			// 当遇到无法被筛去的数时
			if (!forked) {
				pipe(pipes);
				forked = 1;
				if (fork() == 0) {			// 创建一个子进程继续筛选
					close(pipes[1]);
					close(listenfd);
					getPrime(pipes[0]);
				} else {				// 父进程
					close(pipes[0]);
				}
			}
			write(pipes[1], &passed_num, 4);
		}
	}
}

int main (int argc, char* argv[]) {
	int pipes[2];
	pipe(pipes);
	for (int i = 2; i <= 35; i++) {
		write(pipes[1], &i, 4);
	}
	close(pipes[1]);
	getPrime(pipes[0]);
	exit(0);
}
