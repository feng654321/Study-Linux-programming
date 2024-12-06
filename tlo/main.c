// main.c
#include <stdio.h>
#include "math.h"

int main() {
	int sum = 0;
	int res = 0;
	int i = 0;
	for(i = 0; i < 100000000; ++i) { // 重复调用以显著拉长执行时间
			sum += add(i, i);
			res += multiply(i, i);
	}
    printf("Sum: %d, Res: %d\n", sum,res);
    return 0;
}

