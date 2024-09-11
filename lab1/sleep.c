#include "kernel/types.h"
#include "user/user.h"

int main (int argc, char *argv[]) {
	if (argc != 2) {		// 格式不正确，输出错误提示
		write(2, "Usage: sleep [time: number]\n", strlen("Usage: sleep time\n"));
		exit(1);
	}
	int _time = atoi(argv[1]);	// 转为整型
	sleep(_time);			// 调用底层函数
	exit(0);
}
