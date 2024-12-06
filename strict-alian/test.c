#include <stdio.h>

void example() {
    int a = 10;
    float *fp = (float*)&a;
    *fp = 3.14f;
    printf("a = %d\n", a);
}

int main() {
    example();
    return 0;
}

